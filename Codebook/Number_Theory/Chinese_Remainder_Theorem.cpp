typedef long long LL;
typedef pair<LL, LL> PLL;
PLL exd_gcd(LL a, LL b) {
  if (a % b == 0) return {0, 1};
  PLL T = exd_gcd(b, a % b);
  return {T.second, T.first - a / b * T.second};
}
LL CRT(vector<PLL> &eqs) {
  LL prod = 1, ans = 0, ni, ns;
  for (auto P: eqs) prod *= P.second;
  for (auto P: eqs) {
    ni = P.second, ns = prod / ni;
    (ans += ns * P.first % prod * exd_gcd(ni, ns).second) %= prod;
  }
  return (LL) (ans + prod) % prod;
}
