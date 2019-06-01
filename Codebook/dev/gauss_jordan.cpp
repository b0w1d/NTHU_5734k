template <typename T> // solve(aX = b), a <- a^-1, b <- X, returns det(a)
T gauss_jordan(vector<vector<T>> &a, vector<vector<T>> &b, function<bool(T)> is_zero) {
  const int n = a.size();
  const int m = b[0].size();
  assert(n == a[0].size());
  assert(n == b.size());
  vector<int> used(n);
  vector<int> row(n);
  vector<int> col(n);
  T det = 1;
  for (int i = 0; i < n; ++i) {
    int pj = -1;
    int pk = -1;
    for (int j = 0; j < n; ++j) {
      if (used[j]) continue;
      for (int k = 0; k < n; ++k) {
        if (used[k]) continue;
        if (pj == -1 || abs(a[pj][pk]) < abs(a[j][k])) {
          pj = j;
          pk = k;
        }
      }
    }

    assert(!is_zero(a[pj][pk]));  // Otherwise matrix is singular

    used[pk] = 1;
    swap(a[pj], a[pk]);
    swap(b[pj], b[pk]);
    if (pj != pk) det = det * -1;
    row[i] = pj;
    col[i] = pk;

    T w = T(1) / a[pk][pk];
    det = det * a[pk][pk];
    a[pk][pk] = 1;
    for (int p = 0; p < n; ++p) a[pk][p] = a[pk][p] * w;
    for (int p = 0; p < m; ++p) b[pk][p] = b[pk][p] * w;
    for (int p = 0; p < n; ++p) {
      if (p == pk) continue;
      w = a[p][pk];
      a[p][pk] = 0;
      for (int q = 0; q < n; ++q) a[p][q] = a[p][q] - a[pk][q] * w;
      for (int q = 0; q < m; ++q) b[p][q] = b[p][q] - b[pk][q] * w;
    }
  }

  for (int p = n - 1; ~p; --p) {
    if (row[p] == col[p]) continue;
    for (int k = 0; k < n; ++k) {
      swap(a[k][row[p]], a[k][col[p]]);
    }
  }

  return det;
}
