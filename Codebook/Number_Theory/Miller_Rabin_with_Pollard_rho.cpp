// Miller_Rabin
LL abs(LL a) {return a > 0? a: -a;}
LL mul(LL x, LL y, LL mod) {
  LL ans = 0, m = x, s = 0, sgn = (x > 0) xor (y > 0)? -1: 1;
  for (x = abs(x), y = abs(y); y; y >>= 1, m <<= 1, m = m >= mod? m - mod: m) 
    if (y&1) s += m, s = s >= mod? s - mod: s;
  return s * sgn;
}
LL modpow(LL x, LL p, LL mod){
  LL s = 1, m = x % mod;
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
  if (n&1^1) return n == 2;
  LL u = n - 1, t = 0;
  // n == u << t
  while (u&1^1) u >>= 1, ++t;
  while (s--) {
    LL a = wits[s] % n;
    if (a and witness(a, n, u, t)) return 0;
  }
  return 1;
}
// Pollard_rho
LL f(LL x, LL n) {
  return mul(x, x, n) + 1;
}
LL pollard_rho(LL n) {
  int cnt = 0;
  if (n&1^1) return 2;
  while (true) {
    LL x = rand() % (n - 1) + 1, y = 2, d = 1;
    for (int sz = 2; d == 1; sz <<= 1) {
      for (int i = 0; i < sz and d <= 1; ++i) 
        x = f(x, n), d = __gcd(abs(x - y), n);
      y = x;
    }
    if (d and n - d) return d;
  }
}
