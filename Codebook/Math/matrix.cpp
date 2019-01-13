#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;

template<typename F>
class Matrix {

  int rowNum, colNum;
  vector<vector<F>> cell;

public:

  Matrix(int n) : rowNum(n), colNum(n) { // Identity matrix
    cell = vector<vector<F>>(n, vector<F>(n, 0));
    for (int i = 0; i < n; i++) cell[i][i] = (F) 1;
  }

  Matrix(int n, int m, int fill = 0) : rowNum(n), colNum(m) {
    cell.assign(n, vector<F>(m, fill));
  }

  Matrix(const Matrix &mat) : rowNum(mat.rowNum), colNum(mat.colNum) { 
    cell = mat.cell; 
  }

  vector<F>& operator[] (int i) { return cell[i]; }

  const vector<F>& operator[] (int i) const { return cell[i]; }

  Matrix& operator= (const Matrix &mat) {
    rowNum = mat.rowNum;
    colNum = mat.colNum;
    cell = mat.cell;
    return *this;
  }

  Matrix& operator*= (const Matrix &mat) {
    assert(colNum == mat.rowNum);
    Matrix res(rowNum, mat.colNum);
    for (int i = 0; i < rowNum; i++) {
      for (int j = 0; j < mat.colNum; j++) {
        for (int k = 0; k < colNum; k++) {
          res[i][j] += cell[i][k] * mat[k][j];
        }
      }
    }
    return *this = res;
  }

  Matrix& operator^= (long long p) {
    assert(rowNum == colNum && p >= 0);
    Matrix res(rowNum);
    for (; p; p >>= 1) {
      if (p&1) res *= *this;
      *this *= *this;
    }
    return *this = res;
  }

  friend istream& operator>> (istream &is, Matrix &mat) {
    for (int i = 0; i < mat.rowNum; i++) 
      for (int j = 0; j < mat.colNum; j++) 
        is >> mat[i][j];
    return is;
  }

  friend ostream& operator<< (ostream &os, const Matrix &mat) {
    for (int i = 0; i < mat.rowNum; i++) 
      for (int j = 0; j < mat.colNum; j++) 
        os << mat[i][j] << " \n"[j == mat.colNum - 1];
    return os;
  }
  Matrix operator* (const Matrix &b) {
    Matrix res(*this);
    return (res *= b);
  }
  Matrix operator^ (const long long p) {
    Matrix res(*this);
    return (res ^= p);
  }
};
