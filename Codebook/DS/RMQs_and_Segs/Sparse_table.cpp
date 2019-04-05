template <class T>
struct SparseTable {
  vector<vector<T>> st;
  function<T(T, T)> op;
  int n;
  SparseTable(const vector<T> &A, const function<T(T, T)> binaryOp) {
    n = A.size(), op = binaryOp;
    int lg = 31 - __builtin_clz(n);
    st.assign(lg + 1, vector<T>(n));
    for (int i = 0; i < n; ++i) st[0][i] = A[i];
    for (int j = 1; (1<<j) <= n; ++j) for (int i = 0; i + (1<<j) <= n; ++i)
      st[j][i] = binaryOp(st[j - 1][i], st[j - 1][i + (1<<(j - 1))]);
  }
  T rmq(int i, int j) {
    assert(i < j);
    int k = 31 - __builtin_clz(j - i);
    return op(st[k][i], st[k][j - (1<<k)]);
  }
  /*
  Exmaple for calling contructor
  SparseTable ST(A, [](int a, int b) { return max(a, b); });
  */
};
