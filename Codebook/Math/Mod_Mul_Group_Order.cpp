#include "Miller_Rabin_with_Pollard_rho.cpp"
LL phi(LL m) {
  auto fac = factor(m);
  return accumulate(fac.begin(), fac.end(), m, [](LL a, pair<LL, int> p_r) {
    return a / p_r.first * (p_r.first - 1);
  });
}
LL order(LL x, LL m) {
  // assert(__gcd(x, m) == 1);
  LL ans = phi(m);
  for (auto P: factor(ans)) {
    LL p = P.first, t = P.second;
    for (int i = 0; i < t; ++i) {
      if (powmod(x, ans / p, m) == 1) ans /= p;
      else break;
    }
  }
  return ans;
}
LL cycles(LL a, LL m) {
  if (m == 1) return 1;
  return phi(m) / order(a, m);
}