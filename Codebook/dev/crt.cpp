int crt(const vector<int> &a, const vector<int> &m) {
  int M = 1;
  for (int i = 0; i < m.size(); ++i) {
    M *= m[i];
  }
  int res = 0;
  for (int i = 0; i < a.size(); ++i) {
    int Mi = M / m[i];
    int rMi = mod_inv(Mi, m[i]);
    (res += 1LL * Mi * rMi % M * a[i] % M) %= M;
  }
  if (res < 0) res += M;
  return res;
}