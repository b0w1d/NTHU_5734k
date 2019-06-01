// will also find multiple roots, in increasing order
vector<double> poly_roots(vector<double> a) {
  static const double EPS = 1e-11;
  static const double INF = 1e12;
  while (a.size() && abs(a.back()) < EPS) a.pop_back();
  assert(a.size());
  vector<double> res;
  if (a.size() == 2) {
    if (EPS < abs(a[1])) res.push_back(-a[0] / a[1]);
    return res;
  }
  vector<double> b(a.size() - 1);
  for (int i = 0; i + 1 < a.size(); ++i) b[i] = a[i + 1] * (i + 1);
  vector<double> broots = poly_roots(b);
  broots.insert(broots.begin(), -INF);
  broots.push_back(INF);
  for (int i = 0; i + 1 < broots.size(); ++i) {
    auto bsearch = [](const vector<double> &a, double lb, double ub) {
      auto eval = [](const vector<double> &a, double x) {
        double t = 1;
        double sum = 0;
        for (double v : a) sum += v * t, t *= x;
        return sum;
      };
      double e_lb = eval(a, lb);
      double e_ub = eval(a, ub);
      if (abs(e_lb) < EPS) return lb;
      if (abs(e_ub) < EPS) return ub;
      if (e_lb * e_ub > 0) return INF;
      for (int _ = 0; _ < 100 && EPS < ub - lb; ++_) {
        double mb = (lb + ub) / 2;
        double e_mb = eval(a, mb);
        if (abs(e_mb) < EPS) return mb;
        (e_lb * e_mb < 0 ? ub : lb) = mb;
      }
      return ub;
    };
    double x = bsearch(a, broots[i], broots[i + 1]);
    if (x < INF) res.push_back(x);
  }
  return res;
}
