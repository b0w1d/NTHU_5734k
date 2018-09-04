struct Lagrange_poly {
  vector<LL> fac, p;
  int n;
  Lagrange_poly(vector<LL> p) : p(p) {
    n = p.size();
    fac.resize(n), fac[0] = 1;
    for (int i = 1; i < n; ++i) fac[i] = fac[i - 1] * i % MOD;
  }
  LL solve(LL x) {
    if (x < n) return p[x];
    LL ans = 0, to_mul = 1;
    for (int j = 0; j < n; ++j) (to_mul *= MOD - x + j) %= MOD;
    for (int j = 0; j < n; ++j) {
      (ans += p[j] * to_mul % MOD *
      powmod(MOD - x + j, MOD - 2, MOD) % MOD *
      powmod(fac[n - 1 - j], MOD - 2, MOD) % MOD *
      powmod(j&1? MOD - fac[j]: fac[j], MOD - 2, MOD)) %= MOD;
    }
    return ans;
  }
};
