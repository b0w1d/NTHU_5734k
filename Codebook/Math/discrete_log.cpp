LL discrete_log(LL b, LL p, LL n) {
  map<LL, LL> att;
  LL m = sqrt((double)p) + 1, M = powmod(b, m * (p - 2), p);
  for (LL cur = 1, i = 0; i < m; ++i, cur = cur * b % p)
    if (not att.count(cur)) att[cur] = i;
  for (LL cur = 1, i = 0; i * m < p - 1; ++i, cur = cur * M % p) 
    if (att.count(n * cur % p)) 
      return (att[cur * n % p] + i * m) % (p - 1);
  return -1;
}
// find x s.t. b**x % p == n with complexity O(sqrt(N))
// return the smallest
// return -1 if ans doesn't exist

// ---------------------------------------------------------------

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
