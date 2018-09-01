#include "Lines.cpp"
template<typename T, typename Real = double>
struct Poly{
  vector<Pt<T>> gon;
  Poly() {}
  Poly(vector<Pt<T>> V): gon(V) {}
  Pt<T>& operator[](size_t k) { return gon[k]; }
  Poly get_hull() {
    auto p = gon;
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    int n = p.size(), m = 0;
    vector<Pt<T>> ch(n + 1);
    for (int i = 0; i < n; ++i) { // note that border is cleared
      while (m > 1 && Line<T>(ch[m - 2], ch[m - 1]).ori(p[i]) <= 0) --m;
      ch[m++] = p[i];
    }
    for (int i = n - 2, k = m; i >= 0; --i) {
      while (m > k && Line<T>(ch[m - 2], ch[m - 1]).ori(p[i]) <= 0) --m;
      ch[m++] = p[i];
    }
    ch.erase(ch.begin() + m - (n > 1), ch.end());
    rotate(ch.begin(), min_element(ch.begin(), ch.end()), ch.end());
    return Poly(ch);
  }
};
