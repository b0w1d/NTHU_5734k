#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<double>> mat;
mat F(mat vec) {
  double x = vec[0][0], y = vec[1][0];
  return mat({{1 + x * x - y * y + exp(x) * cos(y)}, {2 * x * y + exp(x) * sin(y)}});
}
mat H(mat X, mat FX) {
  double x = X[0][0], y = X[1][0], fx = FX[0][0], fy = FX[1][0],
         f11 = 2 * x + exp(x) * cos(y),
         f12 = -2 * y - exp(x) * sin(y),
         f21 = 2 * y + exp(x) * sin(y),
         f22 = 2 * x + exp(x) * cos(y);
  double det = f11 * f22 - f12 * f21;
  return mat({{f22 / det * fx + -f12 / det * fy}, {-f21 / det * fx + f11 / det * fy}});
}
mat sub(mat A, mat B) {
  for (int k = 0; k < A.size(); ++k) for (int j = 0; j < A[0].size(); ++j) {
    A[k][j] -= B[k][j];
  }
  return A;
}
ostream& operator<<(ostream &os, const mat &X) {
  for (auto v: X) {
    for (int i = 0; i < v.size(); ++i) 
      os << fixed << setprecision(10) << v[i] << " \n"[i + 1 == v.size()];
  }
  return os;
}
mat find_root(mat X = {{-1}, {4}}) {
  for (int _ = 0; _ < 1000; ++_) {
    X = sub(X, H(X, F(X)));
    auto FX = F(X);
    cout << FX << '\n';
  }
  return X;
}
int main() { find_root(); }
