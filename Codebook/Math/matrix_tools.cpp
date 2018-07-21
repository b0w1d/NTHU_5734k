typedef vector<vector<LL>> mat;
const int dim = 3; // dimension;
const mat Id = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}; 
// modify it if diemnsion != 2
LL MOD = 1e9 + 7;
mat mul(mat A, mat B) {
  assert(A[0].size() == B.size());
  mat ans(A.size(), vector<LL>(B[0].size(), 0));
  for (int k = 0; k < B.size(); ++k)
    for (int i = 0; i < A.size(); ++i)
      for (int j = 0; j < B[0].size(); ++j)
        (ans[i][j] += A[i][k] * B[k][j]) %= MOD;
  return ans;
}
mat mat_pow(mat A, LL k) {
  assert(A.size() == A[0].size());
  mat ans = Id;
  for (mat cur = A; k; k >>= 1, cur = mul(cur, cur))
    if (k&1) ans = mul(ans, cur);
  return ans;
}
void print_mat(mat A) {
  for (int i = 0; i < A.size(); ++i) 
    for (int j = 0; j < A[i].size(); ++j)
      cout << A[i][j] << " \n"[j == A[i].size() - 1];
}