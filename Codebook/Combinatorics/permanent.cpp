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