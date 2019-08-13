template <typename T, typename Real = double>
struct Line {
  Pt<T> st, ed;
  Pt<T> vec() const { return ed - st; }
  T ori(const Pt<T> p) const { return (ed - st)^(p - st); }
  Line(const Pt<T> x, const Pt<T> y) : st(x), ed(y) {}
  template<class F> operator Line<F> () const {
    return Line<F>((Pt<F>)st, (Pt<F>)ed);
  }

  // sort by arg, the left is smaller for parallel lines
  bool operator<(Line B) const {
    Pt<T> a = vec(), b = B.vec();
    auto sgn = [](const Pt<T> t) { return (t.y == 0? t.x: t.y) < 0; };
    if (sgn(a) != sgn(b)) return sgn(a) < sgn(b);
    if (abs(a^b) == 0) return B.ori(st) > 0;
    return (a^b) > 0;
  }

  // Regard a line as a function
  template<typename F> Pt<F> operator()(const F x) const {
    return Pt<F>(st) + vec() * x;
  }

  bool isSegProperIntersection(const Line l) const {
    return l.ori(st) * l.ori(ed) < 0 and ori(l.st) * ori(l.ed) < 0;
  }

  bool isPtOnSegProperly(const Pt<T> p) const {
    return ori(p) == 0 and ((st - p)&(ed - p)) < 0;
  }

  Pt<Real> getIntersection(const Line<Real> l) {
    Line<Real> h = *this;
    return l(((l.st - h.st)^h.vec()) / (h.vec()^l.vec()));
  }

  Pt<Real> projection(const Pt<T> p) const {
    return operator()(((p - st)&vec()) / (Real)(vec().norm()));
  }
};
