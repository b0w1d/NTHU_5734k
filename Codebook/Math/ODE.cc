struct Point {
  long double t, x;
  Point(long double t, long double x) : x(x), t(t) {};
};

class ODE {
  typedef long double Double;
  function<Double(Double, Double)> f; // f(t, x(t)) = dx / dt
  Double x, t;
public:
  ODE(function<Double(Double, Double)> func, 
      Double x, Double t) : x(x), t(t), f(func) {}
  vector<Point> getRungeKuttaTable(Double d, int step = 1e3) {
    Double ct = t, cx = x, h = (d - t) / step;
    vector<Point> ret = {{ct, cx}};
    for (int i = 0; i < step; ++i) {
      auto F1 = h * f(ct, cx);
      auto F2 = h * f(ct + h / 2, cx + F1 / 2);
      auto F3 = h * f(ct + h / 2, cx + F2 / 2);
      auto F4 = h * f(ct + h, cx + F3);
      cx += (F1 + 2 * F2 + 2 * F3 + F4) / 6;
      ct += h;
      ret.emplace_back(ct, cx);
    }
    return ret;
  }
  vector<Point> getAdamsBashforthTable(Double d, int step = 1e3) {
    Double h = (d - t) / step;
    vector<Point> ret = getRungeKuttaTable(t + 4 * h, 4);
    for (int i = 4; i < step; ++i) {
      int n = ret.size();
      auto x = ret[n - 1].x + h / 720 * (
      1901 * f(ret[n - 1].t, ret[n - 1].x) - 2774 * f(ret[n - 2].t, ret[n - 2].x) +
      2616 * f(ret[n - 3].t, ret[n - 3].x) - 1274 * f(ret[n - 4].t, ret[n - 4].x) +
      251 * f(ret[n - 5].t, ret[n - 5].x));
      ret.emplace_back(t + i * h + h, x);
    }
    return ret;
  }
};
