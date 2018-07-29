const int INF = 1e9 + 10;
vector<vector<int>> build_sparse_table(const vector<int> &A) {
  int n = A.size(), lg = 31 - __builtin_clz(n);
  vector<vector<int>> st(lg + 1, vector<int>(n));
  for (int i = 0; i < n; ++i) st[0][i] = A[i];
  for (int j = 1; (1<<j) <= n; ++j)
    for (int i = 0; i + (1<<j) <= n; ++i)
      st[j][i] = min(st[j - 1][i], st[j - 1][i + (1<<(j - 1))]);
  return st;
}
int sparse_rmq(int i, int j, vector<vector<int>> &__ST;) {
  if (i >= j) return INF;
  int n = __ST[0].size(), k = 31 - __builtin_clz(j - i);
  return min(__ST[k][i], __ST[k][j - (1<<k)]);
}
