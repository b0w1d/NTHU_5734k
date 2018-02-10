template<typename T>
vector<int> build_kmp(const T &s) {
  vector<int> f(s.size());
  int fp = f[0] = -1;
  for (int i = 1; i < s.size(); ++i) {
    while (~fp && s[fp + 1] != s[i]) fp = f[fp];
    if (s[fp + 1] == s[i]) ++fp;
    f[i] = fp;
  }
  return fp;
}
