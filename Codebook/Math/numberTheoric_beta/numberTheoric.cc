template<typename F>
tuple<F, F, F> ext_gcd(F a, F b) {
  if (!a) return {0, 1, b}; // true even if sign is negetive
  if (!b) return {1, 0, a};
  F x, y, g;
  tie(x, y, g) = ext_gcd(b, a % b);
  return {y, x - a / b * y, g};
}

template<typename F>
F powM(F x, F p, F mod) {
  F s = 1, m = x % mod;
  for (; p; m = m * m % mod, p >>= 1)
    if (p&1) s = s * m % mod; // or consider int128
  return s;
}

template<typename F>
F dangerous_mul(F a, F b, F mod){ // 10 times faster than the above in average, but could be prone to wrong answer (extreme low prob?)
  return (a * b - (long long)((long double)a * b / mod) * mod) % mod;
}

template<typename F>
vector<F> linear_inv(F p, int k) { // take k
  vector<F> inv(min(p, F(1 + k)));
  inv[1] = 1;
  for (int i = 2; i < inv.size(); ++i)
    inv[i] = (p - p / i) * inv[p % i] % p;
  return inv;
}

namespace LLFactorization {

typedef long long LL;

LL LLmul(LL x, LL y, LL mod) {
  LL m = x, s = 0;
  for (; y; y >>= 1, m <<= 1, m = m >= mod? m - mod: m)
    if (y&1) s += m, s = s >= mod? s - mod: s;
  return s;
}

LL powM(LL x, LL p, LL mod) {
  LL s = 1, m = x % mod;
  for (; p; m = LLmul(m, m, mod), p >>= 1)
    if (p&1) s = LLmul(s, m, mod); // or consider int128
  return s;
}

bool miller_rabin(LL n, int s = 7) {
  const LL wits[7] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
  auto witness = [&](LL a, LL n, LL u, int t) {
    LL x = powM(a, u, n), nx;
    for (int i = 0; i < t; ++i, x = nx) {
      nx = LLmul(x, x, n);
      if (nx == 1 and x != 1 and x != n - 1) return true;
    }
    return x != 1;
  };
  if (n < 2) return 0;
  if (n&1^1) return n == 2;
  LL u = n - 1, t = 0, a; // n == (u << t) + 1
  while (u&1^1) u >>= 1, ++t;
  while (s--)
    if ((a = wits[s] % n) and witness(a, n, u, t)) return 0;
  return 1;
}
// Pollard_rho
LL pollard_rho(LL n) {
  auto f = [=](LL x, LL n) { return LLmul(x, x, n) + 1; };
  if (n&1^1) return 2;
  while (true) {
    LL x = rand() % (n - 1) + 1, y = 2, d = 1;
    for (int sz = 2; d == 1; y = x, sz <<= 1)
      for (int i = 0; i < sz and d <= 1; ++i)
        x = f(x, n), d = __gcd(abs(x - y), n);
    if (d and n - d) return d;
  }
}

template<typename F>
vector<pair<F, int>> factor(F m) {
  vector<pair<F, int>> ans;
  while (m > 2e14) {
    F cur = m;
    while (not miller_rabin(cur)) cur = pollard_rho(cur);
    ans.emplace_back(cur, 0);
    while (m % cur == 0) ++ans.back().second, m /= cur;
  }
  for (long long p = 2; p * p <= m; ++p) {
    if (m % p == 0) {
      ans.emplace_back(p, 0);
      while (m % p == 0) ++ans.back().second, m /= p;
    }
  }
  if (m > 1) ans.emplace_back(m, 1);
  sort(ans.begin(), ans.end());
  return ans;
}
} // namespace LLFactorization

template<typename F>
F phi(F m) {
  auto fac = LLFactorization::factor(m);
  return accumulate(fac.begin(), fac.end(), m, [](F a, pair<F, int> p_r) {
    return a / p_r.first * (p_r.first - 1);
  });
}


template<typename F>
F order(F x, F m) {
  // assert(__gcd(x, m) == 1);
  F ans = phi(m);
  for (auto P: LLFactorization::factor(ans)) {
    F p = P.first, t = P.second;
    for (int i = 0; i < t; ++i) {
      if (LLFactorization::powM(x, ans / p, m) == 1) ans /= p;
      else break;
    }
  }
  return ans;
}

template<typename F>
F cycles(F a, F m) {
  if (m == 1) return 1;
  return phi(m) / order(a, m);
}

template<typename F>
F generator(F p) {
  assert(LLFactorization::miller_rabin(p));
  for (F a = 2; a <= p; ++a) if (order(a, p) == p - 1) return a;
}

template<typename F>
F discrete_log(F b, F n, F M) { // find minimum x s.t. b ^ x mod M == n
  const F NONEXIST = -1;
  map<F, F> att;
  F m = sqrt((double)M) + 1, B = powM(b, m * (M - 2), M); // B = b ^ -m
  for (F cur = 1, i = 0; i < m; ++i, cur = cur * b % M)
    if (not att.count(cur)) att[cur] = i;
  for (F cur = 1, i = 0; i * m < M - 1; ++i, cur = cur * B % M)
    if (att.count(n * cur % M))
      return (att[cur * n % M] + i * m) % (M - 1);
  return NONEXIST;
}

template<typename F>
F discrete_kth_root(F k, F m, F p) { // x**n = m mod p
  F g = generator(p); // in most cases, do precalculate the generator
  F q = discrete_log(g, m, p);
  if (q == -1) return -1;

  F x, y, d;
  tie(x, y, d) = ext_gcd(k, p - 1);
  if (q % d) return -1; // conclusion of no solution by ext_gcd

  F w = x;
  if (w < 0) w = w % ((p - 1) / d) + (p - 1) / d; // normalize to non-negative

  F r = 1; // g**q = g**(n*w') = (g**w')**n -> x = g**w'
  for (F i = q / d * w; i; i >>= 1) {
    if (i & 1) r = r * g % p;
    g = g * g % p;
  }
  return r;
}
