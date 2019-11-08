template<typename Double>
class Integration {
  Double ALPHA = sqrt((5 - sqrt(40. / 7))) / 3, WA = (322 + sqrt(11830)) / 900;
  Double W0 = 128. / 225.;
  Double BETA  = sqrt((5 + sqrt(40. / 7))) / 3, WB = (322 - sqrt(11830)) / 900;
  function<Double(Double)> f;
  Double quadrature(Double l, Double r) {
    auto m = (l + r) / 2, len = r - m;
    return (f(m - ALPHA * len) * WA + f(m - BETA * len) * WB + f(m) * W0 +
            f(m + ALPHA * len) * WA + f(m + BETA * len) * WB) * len;
  }
  Double askArea(Double l, Double r, Double exceptArea) {
    Double m = (l + r) / 2, L = quadrature(l, m), R = quadrature(m, r);
    if (abs(L + R - exceptArea) < 1e-10)
      return L + R;
    else return askArea(l, m, L) + askArea(m, r, R);
  }
public:
  Integration(function<Double(Double)> func) : f(func) {}
  Double intergal(Double l, Double r, int piece = 10) {
    Double ans = 0;
    for (Double dx = (r - l) / piece, i = 0; i < piece; ++i) {
      auto cur = l + dx * i;
      ans += askArea(cur, cur + dx, quadrature(cur, cur + dx));
    }
    return ans;
  }
};