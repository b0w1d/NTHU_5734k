double min_sphere_cover(const vector<Point> &p, Point st) { // tested on N=100, EPS=1e-3, |X|<1e5
  const double EPS = 1e-4;
  const double DECAY_RATE = 0.9998;
  double ans = numeric_limits<double>::max();
  for (double delta = 100; EPS < delta; delta *= DECAY_RATE) {
    Point q =
        *max_element(p.begin(), p.end(), [&](const Point &s, const Point &t) {
          return (s - st).abs() < (t - st).abs();
        });
    double r = (st - q).abs(); // abs(P) = sqrt(P.x^2+P.y^2+P.z^2)
    st = st - (st - q) * (delta / r);
    ans = min(ans, r);
  }
  return ans;
}
