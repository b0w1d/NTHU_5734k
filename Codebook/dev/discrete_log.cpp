int discrete_log(int a, int m, int p) { // a**x = m mod p
  int magic = sqrt(p) + 2;
  map<int, int> mp;
  int x = 1;
  for (int i = 0; i < magic; ++i) {
    mp[x] = i;
    x = 1LL * x * a % p;
  }
  for (int i = 0, y = 1; i < magic; ++i) {
    int inv = get<0>(ext_gcd(y, p));
    if (inv < 0) inv += p;
    int u = 1LL * m * inv % p;
    if (mp.count(u)) return i * magic + mp[u];
    y = 1LL * y * x % p;
  }
  return -1;
}