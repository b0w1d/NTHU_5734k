LL PI(LL m);
const int MAXM = 10000, MAXN = 650, UPBD = 5000000;
// 650 ~ PI(cbrt(1e11))
LL pi[UPBD] = {0}, phi[MAXM][MAXN];
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
  for (int i = 0; i < MAXM; ++i) 
    phi[i][0] = i;
  for (int i = 1; i < MAXM; ++i) 
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
  if (m < MAXM and n < MAXN) return phi[m][n];
  if (n == 0) return m;
  auto p = primes[n - 1];
  if (m < UPBD) {
    if (m <= p * p) return pi[m] - n + 1;
    if (m <= p * p * p) {
      int s2n = pi[(int)sqrt(0.5 + m)];
      LL ans = pi[m] - (s2n + n - 2) * (s2n - n + 1) / 2;
      for(int i = n; i < s2n; i++) ans += pi[m / primes[i]];
      return ans;
    }
  }
  return PHI(m, n - 1) - PHI(m / p, n - 1);
}

LL PI(LL m) {
  if (m < UPBD) return pi[m];
  LL y = cbrt(m) + 10, n = pi[y];
  return PHI(m, n) + n - 1 - P_2(m, n);
}
