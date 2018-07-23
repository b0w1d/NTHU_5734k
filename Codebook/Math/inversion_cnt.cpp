LL sort_and_inv_cnt(vector<int> &A, int s, int e) {
  if (e - s == 1) return 0;
  int m = s + e >> 1;
  LL ans = 0;
  ans += sort_and_inv_cnt(A, s, m);
  ans += sort_and_inv_cnt(A, m, e);
  for (int i = m, j = s; i < e; ++i) {
    while (j < m and A[j] <= A[i]) ++j;
    ans += m - j;
  }
  inplace_merge(A.begin() + s, A.begin() + m, A.begin() + e);
  return ans;
}

