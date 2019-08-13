template<typename T>
vector<T> operator-(vector<T> A, vector<T> B) {
  for (int i = 0; i < A.size(); ++i) A[i] = A[i] - B[i];
  return A;
}

template<typename T>
vector<T> operator*(vector<T> A, T mul) {
  for (int i = 0; i < A.size(); ++i) A[i] = A[i] * mul;
  return A;
}

template<typename T>
vector<T> operator/(vector<T> A, T mul) {
  for (int i = 0; i < A.size(); ++i) A[i] = A[i] / mul;
  return A;
}


template<typename T>
T det(Matrix<T> A) {
  int N = A.rowNum;
  T ans(1);
  for (int r = 0; r < N; ++r) {
    if (A[r][r] == T(0)) return T(0);
    ans = ans * A[r][r];
    for (int pvt = r + 1; pvt < N; ++pvt) {
      A[pvt] = A[pvt] - A[r] * A[pvt][r] / A[r][r];
    }
  }
  return ans;
}
