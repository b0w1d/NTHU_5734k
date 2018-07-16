typedef vector<vector<LL>> mat;
const int dim = 2; // dimension;
const mat Id = {{1, 0}, {0, 1}}; // modify it if diemnsion != 2
LL MOD;
mat mul(mat A, mat B) {
  mat ans(dim, vector<LL>(dim, 0));
  for (int k = 0; k < dim; ++k)
    for (int i = 0; i < dim; ++i)
      for (int j = 0; j < dim; ++j)
        (ans[i][j] += A[i][k] * B[k][j]) %= MOD;
  return ans;
}
mat mat_pow(mat A, int k) {
  mat ans = Id;
  for (mat cur = A; k; k >>= 1, cur = mul(cur, cur))
    if (k&1) ans = mul(ans, cur);
  return ans;
}
void print_mat(mat A) {
  for (int i = 0; i < dim; ++i) for (int j = 0; j < dim; ++j) 
    cout << A[i][j] << " \n"[j == dim - 1];
}
