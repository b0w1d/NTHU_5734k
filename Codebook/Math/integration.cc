#include <bits/stdc++.h>
using namespace std;
class Integration {
  typedef long double Double;
  Double ALPHA = sqrt((5 + sqrt(11)) / 12);
  Double BETA  = sqrt((5 - sqrt(11)) / 12);
  function<Double(Double)> f;
  Double quadrature(Double l, Double r) {
    auto m = (l + r) / 2, len = r - m;
    return (f(m - ALPHA * len) + f(m - BETA * len) + f(m) +
            f(m + ALPHA * len) + f(m + BETA * len)) * (r - l) / 5;
  }
  Double askArea(Double l, Double r, Double exceptArea) {
    Double m = (l + r) / 2, L = quadrature(l, m), R = quadrature(m, r);
    if (abs((L + R - exceptArea) / exceptArea) < 1e-3) return L + R;
    else return askArea(l, m, L) + askArea(m, r, R);
  }
public:
  Integration(function<Double(Double)> func) : f(func) {}
  Double intergal(Double l, Double r, int piece = 1e6) {
    Double ans = 0;
    for (Double dx = (r - l) / piece, i = 0; i < piece; ++i) {
      auto cur = l + dx * i;
      ans += askArea(cur, cur + dx, quadrature(cur, cur + dx));
    }
    return ans;
  }
};
int main() {
  Integration formula([](long double t) {
    return sqrt(1 - t * t);
  });
  cout << fixed << setprecision(20) << 2 * formula.intergal(-1, 1) << '\n';
}

