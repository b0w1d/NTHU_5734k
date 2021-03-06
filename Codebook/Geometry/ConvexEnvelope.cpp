using F = long long;
struct Line {
  static const F QUERY = numeric_limits<F>::max();
  F m, b;
  Line(F m, F b) : m(m), b(b) {}
  mutable function<const Line*()> succ;
  bool operator<(const Line& rhs) const {
    if (rhs.b != QUERY) return m == rhs.m ? b < rhs.b : m < rhs.m;
    const Line* s = succ();
    return s and b - s->b < (s->m - m) * rhs.m;
  }
  F operator()(F x) const { return m * x + b; };
};

struct HullDynamic : public multiset<Line> {
  bool isOnHull(iterator y) { //Mathematically, Strictly
    auto z = next(y);
    if (y == begin()) return z == end() or y->m != z->m or z->b < y->b;
    auto x = prev(y);
    if (z == end()) return x->m != y->m or x->b < y->b;
    if (y->m == z->m) return y->b > z->b;
    if (x->m == y->m) return x->b < y->b;
    return (x->b - y->b) * (z->m - y->m) < (y->b - z->b) * (y->m - x->m);
    // Beware long long overflow
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
