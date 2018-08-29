bool miller_rabin(LL n, int s = 7) {
  const LL wits[7] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
  auto witness = [=](LL a, LL n, LL u, int t) {
    LL x = powmod(a, u, n), nx; // use LLmul, remember
    for (int i = 0; i < t; ++i, x = nx){
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
vector<pair<LL, int>> factor(LL m) {
  vector<pair<LL, int>> ans;
  while (m != 1) {
    LL cur = m;
    while (not miller_rabin(cur)) cur = pollard_rho(cur);
    ans.emplace_back(cur, 0);
    while (m % cur == 0) ++ans.back().second, m /= cur;
  }
  sort(ans.begin(), ans.end());
  return ans;
}