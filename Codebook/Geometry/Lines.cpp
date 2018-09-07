#include "Points.cpp"
template <typename T, typename Real = double>
struct Line {
  Pt<T> p1, p2;
  Line() {}
  Line(const Pt<T> x, const Pt<T> y) : p1(x), p2(y) {}
  Pt<T> vec() const { return p2 - p1; }
  T ori(const Pt<T> p) const { return (p2 - p1) ^ (p - p1); }
  Pt<Real> get_intersection(const Line<Real> &l) {
    Pt<Real> q1 = p1, q2 = p2, qv = vec();
    return q1 + qv * (l.vec() ^ (q1 - l.p1)) / (qv ^ l.vec());
  }
  Real dis_to_Line(const Pt<T> p, bool is_Seg = false) const {
    Pt<T> v1 = p - p1;
    if (is_Seg) {
      Pt<T> v2 = p - p2;
      if ((vec() & v1) <= 0) return abs(v1.norm2());
      if ((vec() & v2) >= 0) return abs(v2.norm2());
    }
    return (vec()^v1) / sqrt(vec().norm2());
  }
  bool is_seg_proper_intersection(const Line& l) const {
    T det1 = l.ori(p1) * l.ori(p2);
    T det2 = ori(l.p1) * ori(l.p2);
    return det1 < 0 and det2 < 0;
  }

  bool is_Pt_on_Seg_properly(const Pt<T> p) const {
    return ori(p) == 0 and ((p1 - p) & (p2 - p)) < 0;
  }
  Pt<Real> projection(const Pt<T> q) const {
    Pt<Real> p = q, n = (p2 - p1).prep();
    return p - n * dis_to_Line(p) / sqrt(n.norm2());
  }
};
