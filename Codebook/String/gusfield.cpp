template<typename T>
vector<int> gusfield(const T &s) {
  vector<int> z(s.size(), s.size()); // z[i] := max k for z[0, k) = z[i, i + k)
  for (int i = 1, L = 0, R = 0; i < s.size(); ++i) {
    if (R <= i) {
      L = R = i;
      while (R < s.size() && s[R] == s[R - L]) ++R;
      z[i] = R - L;
    } else {
      int k = i - L;
      if (z[k] < R - i) {
        z[i] = z[k];
      } else {
        L = i;
        while (R < s.size() && s[R] == s[R - L]) ++R;
        z[i] = R - L;
      }
    }
  }
  return z;
}
