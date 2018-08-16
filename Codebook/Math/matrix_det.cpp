#include <bits/stdc++.h>

using namespace std;

typedef vector<long long> Vec;
typedef vector<Vec> Matrix;

Matrix cofactor(int col, Matrix mat) {
  int n = mat.size();
  Matrix res(n - 1, Vec(mat.size() - 1));
  for (int i = 0, ii = 0; i < n; i++) {
    if (i == col) continue;
    for (int j = 0; j < n - 1; j++) {
      res[j][ii] = mat[j + 1][i];
    }
    ii++;
  }
  return res;
}

long long det(Matrix mat) {
  if (mat.size() == 1) return mat[0][0];
  int res = 0, sign = 1;
  for (int i = 0; i < mat.size(); i++) {
    res += sign * mat[0][i] * det(cofactor(i, mat));
    sign *= -1;
  }
  return res;
}

int main() {
  Matrix mm(2, Vec(2));
  mm[0][0] = 1;
  mm[0][1] = 2;
  mm[1][0] = 3;
  mm[1][1] = 4;
  cout << det(mm) << "\n";
}
