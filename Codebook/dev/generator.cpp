int generator(int p) { // modulo prime p, O(x*log(phi(p))*log(p)), x = O(lg^6p)
  auto fp = PrimeFactor::factorize(p);
  int phi = p;
  for (auto u : fp) phi = phi / u.first * (u.first - 1);
  auto pp = PrimeFactor::factorize(phi);
  auto int_pow = [](int v, int n, int p) {
    int r = 1;
    for (int i = n; i; i >>= 1) {
      if (i & 1) r = 1LL * r * v % p;
      v = 1LL * v * v % p;
    }
    return r;
  };
  auto check = [&](int g) {
    for (auto u : pp) {
      int t = int_pow(g, phi / u.first, p);
      if (t == 1) return false;
    }
    return true;
  };
  for (int i = 2; ; ++i) {
    if (check(i)) return i;
  }
  return -1;
}
