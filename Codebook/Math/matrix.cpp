#include <bits/stdc++.h>

using namespace std;

class Matrix {
  public:
  int row, col;
  vector< vector<int> > ele;

  Matrix(int n) : row(n), col(n) { // Identity matrix
    ele = vector< vector<int> >(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
      ele[i][i] = 1;
    }
  }

  Matrix(int n, int m, int fill = 0) : row(n), col(m) {
    ele.resize(n);
    for (int i = 0; i < n; i++) {
      ele[i] = vector<int>(m, fill);
    }
  }

  Matrix(const Matrix &mat) : row(mat.row), col(mat.col) {
    ele = mat.ele;
  }

  vector<int>& operator[] (int i) {
    return ele[i];
  }

  const vector<int>& operator[] (int i) const {
    return ele[i];
  }

  Matrix& operator= (const Matrix &mat) {
    row = mat.row;
    col = mat.col;
    ele = mat.ele;
    return *this;
  }

  Matrix& operator*= (const Matrix &mat) {
    assert(col == mat.row);
    Matrix res(row, mat.col);
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < mat.col; j++) {
        for (int k = 0; k < col; k++) {
          res[i][j] += ele[i][k] * mat[k][j];
        }
      }
    }
    return *this = res;
  }

  Matrix& operator^= (const int p) {
    assert(row == col && p >= 0);
    Matrix res(row);
    for (int i = p; i > 0; i /= 2) {
      if (i & 1) res *= *this;
      *this *= *this;
    }
    return *this = res;
  }

  friend istream& operator>> (istream &is, Matrix &mat) {
    for (int i = 0; i < mat.row; i++) {
      for (int j = 0; j < mat.col; j++) {
        is >> mat[i][j];
      }
    }
    return is;
  }

  friend ostream& operator<< (ostream &os, const Matrix &mat) {
    for (int i = 0; i < mat.row; i++) {
      for (int j = 0; j < mat.col; j++) {
        os << mat[i][j] << " ";
      }
      os << "\n";
    }
    return os;
  }
};

Matrix operator* (const Matrix &a, const Matrix &b) {
  Matrix res(a);
  return (res *= b);
}

Matrix operator^ (const Matrix &a, const int p) {
  Matrix res(a);
  return (res ^= p);
}

Matrix cofactor(int col, Matrix mat) {
  Matrix res(mat.row - 1, mat.col - 1);
  for (int i = 0, ii = 0; i < mat.row; i++) {
    if (i == col) continue;
    for (int j = 0; j < mat.col - 1; j++) {
      res[j][ii] = mat[j + 1][i];
    }
    ii++;
  }
  return res;
}

int det(Matrix mat) {
  assert(mat.row == mat.col);
  if (mat.row == 1) return mat[0][0];
  int res = 0, sign = 1;
  for (int i = 0; i < mat.col; i++) {
    res += sign * mat[0][i] * det(cofactor(i, mat));
    sign *= -1;
  }
  return res;
}

/* =============================================================== */
// TODO: gaussianEliminate

int main() {
  Matrix mat(2, 3, -1);
  cout << mat << "\n";
  Matrix id(2);
  Matrix ans = id * mat;
  cout << ans << "\n";
  Matrix mat2(3);
  cin >> mat2;
  cout << det(mat2) << "\n";
  return 0;
}
