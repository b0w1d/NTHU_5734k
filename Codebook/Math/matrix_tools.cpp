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
pair<LL, LL> Gaussian_elimination(mat &A) {
  // upper triangular decomposition
  assert(A[0].size() == A.size());
  LL det = 1, rank = 0, n = A.size();
  for (int i = 0; i < n; ++i) {
    int sw = find_if(A.begin() + i, A.end(),
                     [=](vector<LL> col) { return col[i];}) - A.begin();
    if (sw == n) { det = 0; continue; }
    if (sw != i) (det *= MOD - 1) %= MOD, swap(A[sw], A[i]);
    for (int j = i + 1; j < n; ++j) {
      if (A[j][i]) for (int k = n - 1; k >= i; --k) {
        A[j][k] -= A[i][k] * powmod(A[j][i], MOD - 2, MOD) % MOD;
        A[j][k] = (A[j][k] % MOD + MOD) % MOD;
      }
    }
    det *= A[i][i], ++rank;
  }
  return {det, rank};
}
typedef vector<vector<LL> > mat;
LL permanent(mat A) {
  LL n = A.size(), ans = 0, *tmp = new LL[n], add;
  for (int pgray = 0, s = 1, gray, i; s < 1 << n; ++s) {
    gray = s ^ s >> 1, add = 1;
    i = __builtin_ctz(pgray ^ gray);
    for (int j = 0; j < n; ++j) 
      add *= tmp[j] += A[i][j] * (gray>>i&1 ? 1 : -1);
    ans += add * (s&1^n&1? -1 : 1), pgray = gray;
  }
  return ans;
}
// how many ways to put rooks on a matrix with 0,1 as constrain
// 1 - ok to put
// 0 - not ok to put
