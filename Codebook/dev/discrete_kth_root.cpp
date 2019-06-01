int discrete_kth_root(int n, int m, int p) { // x**n = m mod p
  int g = generator(p); // in most cases, do precalculate the generator

  int q = discrete_log(g, m, p);
  if (q == -1) return -1;

  int x, y, d;
  tie(x, y, d) = ext_gcd(n, p - 1);
  
  if (q % d) return -1;

  int w = x;
  if (w < 0) w = w % ((p - 1) / d) + (p - 1) / d;
  
  int r = 1;
  for (int64_t i = 1LL * q / d * w; i; i >>= 1) {
    if (i & 1) r = 1LL * r * g % p;
    g = 1LL * g * g % p;
  }

  return r;
}
