pair<vector<int>, vector<int>> linear_sieve(const int UPBD) {
  vector<int> primes, last_prime(UPBD);
  for (int p = 2; p < UPBD; ++p) {
    if (not last_prime[p]) primes.push_back(p), last_prime[p] = p;
    for (int j = 0; primes[j] * p < UPBD; ++j) {
      last_prime[primes[j] * p] = primes[j];
      if (p % primes[j] == 0) break;
    }
  }
  return {primes, last_prime};
}

class Meissel_Lehmer_PI {
  typedef long long LL;
  int MAXM, MAXN, UPBD;
  // 650 ~ PI(cbrt(1e11))
  vector<int> pi;
  vector<vector<int>> phi;
  vector<int> primes, last_prime;
public:
  LL P_2(LL m, LL n) {
    LL ans = 0;
    for (LL i = n; (LL)primes[i] * primes[i] <= m and i < primes.size(); ++i)
      ans += PI(m / primes[i]) - i;
    return ans;
  }
  LL PHI(LL n, LL m) { // # integer in [1, m] s.t. all divisor larger than p_n 
    if (n < MAXN and m < MAXM) return phi[n][m];
    if (n == 0) return m;
    LL p = primes[n - 1];
    if (m < UPBD) {
      if (m <= p) return 1;
      if (m <= p * p * p) return pi[m] - n + 1 + P_2(m, n);
    }
    return PHI(n - 1, m) - PHI(n - 1, m / p);
  }
  Meissel_Lehmer_PI(const LL MAX_QUERY) {
    assert(MAX_QUERY > 1e6);
    MAXN = cbrt(MAX_QUERY) * 1.1;
    UPBD = sqrt(MAX_QUERY);
    MAXM = UPBD / MAXN;
    phi = vector<vector<int>>(MAXN, vector<int>(MAXM, 0));
    pi.resize(UPBD);
    tie(primes, last_prime) = linear_sieve(UPBD);
    for (int i = 2; i < UPBD; ++i) pi[i] = pi[i - 1] + (last_prime[i] == i);
    iota(phi[0].begin(), phi[0].end(), 0);
    for (int i = 1; i < MAXN; ++i) for (int j = 1; j < MAXM; ++j) 
      phi[i][j] = phi[i - 1][j] - phi[i - 1][j / primes[i - 1]];
  }
  LL PI(LL m) {
    if (m < UPBD) return pi[m];
    int y = cbrt(m) + 10, n = pi[y];
    return PHI(n, m) + n - 1 - P_2(m, n);
  }
};