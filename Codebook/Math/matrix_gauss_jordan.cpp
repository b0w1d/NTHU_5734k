#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-8;
typedef vector<double> Vec;
typedef vector<Vec> Matrix;

// return empty vector if zero or infinite solutions
// time complexity O(n^3)
Vec gauss_jordan(const Matrix &A, const Vec &b) {
  int n = A.size();
  Matrix B(n, Vec(n + 1));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      B[i][j] = A[i][j];
    }
    B[i][n] = b[i];
  }
  for (int i = 0; i < n; i++) {
    int pivot = i;
    for (int j = i; j < n; j++) {
      if (abs(B[j][i]) > abs(B[j][pivot])) {
        pivot = j;
      }
    }
    swap(B[i], B[pivot]);

    if (abs(B[i][i]) < eps) return Vec();

    for (int j = i + 1; j <= n; j++) B[i][j] /= B[i][i];
    // B[i][i] = 1;
    for (int j = 0; j < n; j++) {
      if (i == j) continue;
      for (int k = i + 1; k <= n; k++) {
        B[j][k] -= B[i][k] * B[j][i];
      }
    }
  }
  Vec res(n);
  for (int i = 0; i < n; i++) {
    res[i] = B[i][n];
  }
  return res;
}

int main() {
  Matrix m(3, Vec(3));
  m[0] = {1, -2, 3};
  m[1] = {4, -5, 6};
  m[2] = {7, -8, 10};
  Vec y = {6, 12, 21};
  Vec ans = gauss_jordan(m, y);
  printf("%f %f %f\n", ans[0], ans[1], ans[2]);
  // 1, 2, 3
}
