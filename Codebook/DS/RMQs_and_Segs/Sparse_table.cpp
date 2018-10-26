template <class T>
vector<vector<T>> build_sparse_table(const vector<T> &A) {
  int n = A.size(), lg = 31 - __builtin_clz(n);
  vector<vector<T>> st(lg + 1, vector<T>(n));
  for (int i = 0; i < n; ++i) st[0][i] = A[i];
  for (int j = 1; (1<<j) <= n; ++j)
    for (int i = 0; i + (1<<j) <= n; ++i)
      st[j][i] = max(st[j - 1][i], st[j - 1][i + (1<<(j - 1))]);
  return st;
}

template <class T>
T sparse_rmq(int i, int j, vector<vector<T>> &__ST) {
  assert(i < j);
  int n = __ST[0].size(), k = 31 - __builtin_clz(j - i);
  return max(__ST[k][i], __ST[k][j - (1<<k)]);
}
