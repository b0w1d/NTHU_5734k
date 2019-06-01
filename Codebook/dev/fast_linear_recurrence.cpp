template<typename T>
vector<T> fast_linear_recurrence(const vector<T> &t, long long p) { // O(lg(p) * t.size()**2)
  auto advance = [&](const vector<T> &u) {
    vector<T> v(t.size());
    v[0] = u.back() * t[0];
    for (int i = 1; i < t.size(); ++i) v[i] = u[i - 1] + u.back() * t[i];
    return v;
  };

  vector<vector<T>> kk(2 * t.size(), vector<T>(t.size())); // kk[i] = lambda(t ** i)
  kk[0][0] = 1;
  for (int i = 1; i < 2 * t.size(); ++i) kk[i] = advance(kk[i - 1]);
  if (p < kk.size()) return kk[p];

  auto square = [&](const vector<T> &u) {
    vector<T> v(2 * t.size());
    for (int j = 0; j < u.size(); ++j)
      for (int k = 0; k < u.size(); ++k)
        v[j + k] = v[j + k] + u[j] * u[k];
    for (int j = u.size(); j < v.size(); ++j)
      for (int k = 0; k < u.size(); ++k)
        v[k] = v[k] + v[j] * kk[j][k];
    v.resize(u.size());
    return v;
  };

  vector<T> m(kk[1]);
  for (int i = 62 - __builtin_clzll(p); ~i; --i) {
    m = square(m);
    if (p >> i & 1) m = advance(m);
  }
  
  return m;
}