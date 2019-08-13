template<typename F>
struct Lagrange_poly {
  vector<F> fac, p;
  int n;
  Lagrange_poly(vector<F> p) : p(p) { // f(i) = p[i]
    n = p.size();
    fac.resize(n), fac[0] = 1;
    for (int i = 1; i < n; ++i) fac[i] = fac[i - 1] * F(i);
  }
  F operator()(F x) const {
    F ans(0), to_mul(1);
    for (int j = 0; j < n; ++j) to_mul = to_mul * (F(j) - x);
    assert(not(to_mul == F(0)));
    for (int j = 0; j < n; ++j) {
      ans = ans + p[j] * to_mul / (F(j) - x) /
            fac[n - 1 - j] / (j&1 ? -fac[j] : fac[j]);
    }
    return ans;
  }
};
