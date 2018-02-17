vector<LL> factor(LL N) {
  vector<LL> ans;
  for (LL p = 2, n = N; p * p <= n; ++p)
    if (N % p == 0) {
      ans.push_back(p);
      while (N % p == 0) N /= p;
    }
  if (N != 1) ans.push_back(N);
  return ans;
}
LL find_root(LL p) {
  LL ans = 1;
  for (auto q: factor(p - 1)) {
    LL a = rand() % (p - 1) + 1, b = (p - 1) / q;
    while (powmod(a, b, p) == 1) a = rand() % (p - 1) + 1;
    while (b % q == 0) b /= q;
    ans = mul(ans, powmod(a, b, p), p); 
  }
  return ans;
}
bool is_root(LL a, LL p) {
  for (auto q: factor(p - 1)) 
    if (powmod(a, (p - 1) / q, p) == 1) 
      return false;
  return true;
}
