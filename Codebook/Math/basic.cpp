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