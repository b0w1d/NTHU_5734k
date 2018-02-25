typedef vector<vector<LL> > mat;
LL pernament(mat A) {
  LL n = A.size(), ans = 0, pgray = 0, *tmp = new LL[n], add;
  for (int s = 1, gray, i; s < 1 << n; ++s) {
    gray = s ^ s >> 1;
    add = 1;
    i = __builtin_ctz(pgray ^ gray);
    for (int j = 0; j < n; ++j) 
      tmp[j] += A[i][j] * (gray>>i&1 ? 1 : -1),
      add *= tmp[j];
    ans += add * (s&1 ? -1 : 1);
    pgray = gray;
  }
  return ans;
}
// how many ways to put rooks on a matrix A with 0,1 as constrain
// 1 - ok to put
// 0 - not ok to put
