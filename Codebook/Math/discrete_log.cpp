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

/*
  solve a ^ x = b (mod m)
  a ^ np = b * a ^ q
  time: O(m log m)
*/
int discrete_log(int a, int b) {
  int n = sqrt(md) + 1;
  int an = power(a, n);

  map<int,int> vals;
  for (int p = 1, cur = an; p <= n; p++) {
    vals[cur] = p;
    cur = mul(cur, an);
  }
  for (int q = 0, cur = b; q < n; q++) {
    if (vals.count(cur)) {
      return vals[cur] * n - q;
    }
    cur = mul(cur, a);
  }
  return -1;
}
