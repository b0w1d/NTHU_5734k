LL PI(LL m);
const int MAXN = 5000, UPBD = MAXN * MAXN;
LL pi[UPBD] = {0}, phi[MAXN][MAXN];
vector<LL> primes;
void init() {
  fill(pi + 2, pi + UPBD, 1);
  for (LL p = 2; p < UPBD; ++p) 
    if (pi[p]) {
      for (LL N = p * p; N < UPBD; N += p) 
        pi[N] = 0;
      primes.push_back(p);
    }
  for (int i = 1; i < UPBD; ++i) pi[i] += pi[i - 1];
  for (int i = 0; i < MAXN; ++i) 
    phi[i][0] = i, phi[1][i] = 1;
  for (int i = 2; i < MAXN; ++i) 
    for (int j = 1; j < MAXN; ++j)
      phi[i][j] = phi[i][j - 1] - phi[i / primes[j - 1]][j - 1];
}
LL P_2(LL m, LL n) {
  LL ans = 0;
  for (LL i = n; primes[i] * primes[i] <= m and i < primes.size(); ++i) 
    ans += PI(m / primes[i]) - i;
  return ans;
}
LL PHI(LL m, LL n) {
  if (m < MAXN and n < MAXN) return phi[m][n];
  if (n == 0) return m;
  return PHI(m, n - 1) - PHI(m / primes[n - 1], n - 1);
}
LL PI(LL m) { // m * m > UPBD
  if (m < UPBD) return pi[m];
  LL y = cbrt(m) + 10, n = pi[y];
  return PHI(m, n) + n - 1 - P_2(m, n);
}
