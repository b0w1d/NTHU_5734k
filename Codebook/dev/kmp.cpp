template<typename T>
vector<int> build_kmp(const T &s) {
  vector<int> f(s.size());
  int fp = f[0] = -1;
  for (int i = 1; i < s.size(); ++i) {
    while (~fp && s[fp + 1] != s[i]) fp = f[fp];
    if (s[fp + 1] == s[i]) ++fp;
    f[i] = fp;
  }
  return f;
}
template<typename S>
vector<int> kmp_match(vector<int> fail, const S &P, const S &T) {
  vector<int> res; // start from these points
  const int n = P.size();
  for (int j = 0, i = -1; j < T.size(); ++j) {
    while (~i and T[j] != P[i + 1]) i = fail[i];
    if (P[i + 1] == T[j]) ++i;
    if (i == n - 1) res.push_back(j - n + 1), i = fail[i];
  }
  return res;
}
