struct Line {
  static const F QUERY = numeric_limits<F>::max();
  F m, b;
  Line(F m, F b) : m(m), b(b) {}
  mutable function<const Line*()> succ;
  bool operator<(const Line& rhs) const {
    if (rhs.b != QUERY) return m < rhs.m;
    const Line* s = succ();
    F x = rhs.m;
    return s and b - s->b < (s->m - m) * x;
  }
  F operator()(F x) const { return m * x + b; };
};
 
struct HullDynamic : public multiset<Line> {
  F ceil2(F a, F b) { return a >= 0 ? (a + b - 1) / b : a / b; };
  bool isOnHull(iterator y) {
    auto z = next(y);
    if (y == begin()) return z == end() or y->m != z->m or z->b < y->b;
    auto x = prev(y);
    if (z == end()) return x->m != y->m or x->b < y->b;
    return ceil2(x->b - y->b, y->m - x->m) < ceil2(y->b - z->b, z->m - y->m);
  }
  void insertLine(F m, F b) {
    auto y = insert(Line(m, b));
    y->succ = [=] { return next(y) == end() ? nullptr : &*next(y); };
    if (not isOnHull(y)) { erase(y); return; }
    while (next(y) != end() and not isOnHull(next(y))) erase(next(y));
    while (y != begin() and not isOnHull(prev(y))) erase(prev(y));
  }
  F operator()(F x) { return (*lower_bound(Line{x, Line::QUERY}))(x); }
};
