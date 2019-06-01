template<typename T>
vector<vector<T>> mat_mul(const vector<vector<T>> &a, const vector<vector<T>> &b) {
  assert(a[0].size() == b.size());
  vector<vector<T>> c(a.size(), vector<T>(b[0].size()));
  for (int i = 0; i < a.size(); ++i) {
    for (int j = 0; j < b.size(); ++j) {
      for (int k = 0; k < b[0].size(); ++k) {
        c[i][k] = c[i][k] + a[i][j] * b[j][k];
      }
    }
  }
  return c;
}

template<typename T>
vector<vector<T>> mat_pow(vector<vector<T>> a, const int p) {
  assert(a.size() == a[0].size());
  vector<vector<T>> r(a.size(), vector<T>(a.size()));
  for (int i = 0; i < r.size(); ++i) r[i][i] = 1;
  for (int i = p; i; i /= 2) {
    if (i & 1) r = mat_mul(r, a);
    a = mat_mul(a, a);
  }
  return r;
}
