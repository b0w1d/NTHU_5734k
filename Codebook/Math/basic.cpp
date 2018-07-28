PLL exd_gcd(LL a, LL b) {
  if (a % b == 0) return {0, 1};
  PLL T = exd_gcd(b, a % b);
  return {T.second, T.first - a / b * T.second};
}
LL powmod(LL x, LL p, LL mod) {
  LL s = 1, m = x % mod;
  for (; p; m = m * m % mod, p >>= 1)
    if (p&1) s = s * m % mod; // or consider int128
  return s;
}
LL LLmul(LL x, LL y, LL mod) {
  LL ans = 0, m = abs(x), s = 0, sgn = (x > 0) xor (y > 0)? -1: 1;
  for (x = abs(x), y = abs(y); y; y >>= 1, m <<= 1, m = m >= mod? m - mod: m)
    if (y&1) s += m, s = s >= mod? s - mod: s;
  return (s * sgn % mod + mod) % mod;
}
LL dangerous_mul(LL a, LL b, LL mod){ // 10 times faster than the above in average, but could be prone to wrong answer (extreme low prob?)
  return (a * b - (LL)((long double)a * b / mod) * mod) % mod;
}
vector<LL> linear_inv(LL p, int k) { // take k
  vector<LL> inv(min(p, 1ll + k));
  inv[1] = 1;
  for (int i = 2; i < inv.size(); ++i)
    inv[i] = (p - p / i) * inv[p % i] % p;
  return inv;
}
inline LL add(LL _x, LL _y, LL _mod = 1e9 + 7) {
  ll _ = _x + _y;
  if (_ >= _mod) _ -= _mod;
  if (_ < 0) _ += mod;
  return _;
}
inline LL mul(LL _x, LL _y, LL _mod = 1e9 + 7) {
  ll _ = _x * _y;
  if (_ >= _mod) _ %= _mod;
  return _;
}