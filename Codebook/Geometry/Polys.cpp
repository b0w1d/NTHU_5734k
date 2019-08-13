template <class F> using Polygon = vector<Pt<F>>;

template<typename T>
T twiceArea(Polygon<T> Ps) {
  int n = Ps.size();
  T ans = 0;
  for (int i = 0; i < n; ++i)
    ans += Ps[i] ^ Ps[i + 1 == n ? 0 : i + 1];
  return ans;
}

template <class F>
Polygon<F> getConvexHull(Polygon<F> points) {
  sort(begin(points), end(points));
  Polygon<F> hull;
  hull.reserve(points.size() + 1);
  for (int phase = 0; phase < 2; ++phase) {
    auto start = hull.size();
    for (auto& point : points) {
      while (hull.size() >= start + 2 and
             Line<F>(hull.back(), hull[hull.size() - 2]).ori(point) <= 0)
        hull.pop_back();
      hull.push_back(point);
    }
    hull.pop_back();
    reverse(begin(points), end(points));
  }
  if (hull.size() == 2 and hull[0] == hull[1]) hull.pop_back();
  return hull;
}

