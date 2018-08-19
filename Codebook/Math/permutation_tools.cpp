vector<int> permutation_inverse(vector<int> P) {
  vector<int> ret(P.size());
  for (int i = 0; i < P.size(); ++i) ret[P[i]] = i;
  return ret;
}
vector<int> composite(vector<int> A, vector<int> B) {
  // can be not a permuation, 0-index is require
  assert(A.size() == B.size());
  int n = A.size();
  vector<int> ret(n);
  for (int i = 0; i < n; ++i) ret[i] = A[B[i]];
  return ret;
}
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
int cycle_cnt(vector<int> P) {
  vector<bool> vis(P.size(), false);
  int cnt = 0;
  for (int i = 0; i < P.size(); ++i) if (not vis[i]) {
    int v = i;
    ++cnt;
    while (not vis[v]) vis[v] = true, v = P[v];
  }
  return cnt;
}
LL permutation_distance(vector<int> P1, vector<int> P2) {
  assert(P1.size() == P2.size());
  P1 = permutation_inverse(P1);
  for (int i = 0; i < P2.size(); ++i) P2[i] = P1[P2[i]];
  return P2.size() - cycle_cnt(P2); // for swap arbitrary element
  // return P2.size() - sort_and_inv_cnt(P2, 0, P2.size()); // for swap adj element
}