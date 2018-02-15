template<typename T, int INF>
vector<int> manacher(const T &s) { // p = "INF" + s.join("INF") + "INF", returns radius on p
  vector<int> p(s.size() * 2 + 1, INF);
  for (int i = 0; i < s.size(); ++i) {
    p[i << 1 | 1] = s[i];
  }
  vector<int> w(p.size());
  for (int i = 1, j = 0, r = 0; i < p.size(); ++i) {
    int t = min(r >= i ? w[2 * j - i] : 0, r - i + 1);
    for ( ; i - t >= 0 && i + t < p.size(); ++t) {
      if (p[i - t] != p[i + t]) break;
    }
    w[i] = --t;
    if (i + t > r) r = i + t, j = i;
  }
  return w;
}
