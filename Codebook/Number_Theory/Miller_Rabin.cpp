#include <bits/stdc++.h>
typedef long long LL;

LL __gcd(LL a, LL b) {
  if (!a or !b) return a|b;
  return __gcd(b, a % b);
}


LL mul(LL x, LL y, LL mod) {
  LL ans = 0, m = x % mod, s = 0, sgn = (x > 0) xor (y > 0)? -1: 1;
  for (x = abs(x), y = abs(y); y; y >>= 1, (m *= 2) %= mod) 
    if (y&1) (s += m) %= mod;
  return s * sgn;
}
LL modpow(LL x, LL p, LL mod){
  LL s = 1, m = x;
  for (; p; m = mul(m, m, mod), p >>= 1) 
    if (p&1) s = mul(s, m, mod);
  return s;
}

bool witness(LL a, LL n, LL u, int t) {
  LL x = modpow(a, u, n), nx;
  for (int i = 0; i < t; ++i, x = nx){
    nx = mul(x, x, n);
    if (nx == 1 and x != 1 and x != n - 1) return 1;
  }
  return x != 1;
}
const LL wits[7] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
bool miller_rabin(LL n, int s = 7) {
  if (n < 2) return 0;
  if (!(n & 1)) return n == 2;
  LL u = n - 1, t = 0;
  // n == u << t
  while (!(u&1)) u >>= 1, ++t;
  while (s--) {
    LL a = wits[s] % n;
    if (a and witness(a, n, u, t)) return 0;
  }
  return 1;
}

LL f(LL x, LL n) {
  return (mul(x, x, n) + 1) % n;
}
LL pollard_rho(LL n) {
  if (n&1^1) return 2;
  while (true) {
    LL x = rand() % (n - 1) + 1, y = 2, d = 1;
    for (LL sz = 2; d <= 1; sz <<= 1) {
      for (int i = 0; i < sz and d <= 1; ++i) 
        x = f(x, n), d = __gcd(abs(x - y), n);
      y = x;
    }
    if (n - d) return d;
  }
}

int main() {
  LL a, d;
  int n; scanf("%d", &n);
  while (n--) {
    scanf("%lld", &a);
    bool found = 0;
    for (int i = 2; i < std::min(n, 1<<20) and not found; ++i) if (a % i == 0) found = 1, printf("%d\n", i);
    if (miller_rabin(a)) puts("Prime");
    else d = pollard_rho(a), printf("%lld\n", std::min(d, a / d));
  }
}
