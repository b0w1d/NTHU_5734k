template <typename T, typename Real = double>
struct Pt {
  T x, y;
  Pt() : x(0), y(0) {}
  Pt(const T x, const T y) : x(x), y(y) {}
  template <class F> operator Pt<F> () const {
    return Pt<F>((F)x, (F)y); }
  Pt& operator=(const Pt b) { x = b.x, y = b.y; return *this; }
  Pt operator+(const Pt b) const { return Pt(x + b.x, y + b.y); }
  Pt operator-(const Pt b) const { return Pt(x - b.x, y - b.y); }
  template <class F> Pt<F> operator* (const F fac) {
    return Pt<F>(x * fac, y * fac); }
  template <class F> Pt<F> operator/ (const F fac) {
    return Pt<F>(x / fac, y / fac); }
  T operator&(const Pt b) const { return x * b.x + y * b.y; }
  T operator^(const Pt b) const { return x * b.y - y * b.x; }
  bool operator==(const Pt b) const { return x == b.x and  y == b.y; }
  bool operator<(const Pt b) const { return x == b.x? y < b.y: x < b.x; }

  Pt operator-() const { return Pt() - *this; }
  Pt prep() const { return Pt(-y, x); }
  T norm2() const { return *this & *this; }
  double rad() const { return atan2(x, y); }
  double angle(Pt<int> a) {
    return acos((*this & a) / sqrt(norm2()) / sqrt(a.norm2())); }
  Pt<Real> rotate(double arg) {
    return Pt<Real>(cos(arg) * x - sin(arg) * y,
                    sin(arg) * x + cos(arg) * y);
  }
};
template<class F> istream& operator>>(istream& is, Pt<F> &pt) {
  return is >> pt.x >> pt.y; }
template <class F> ostream& operator<<(ostream& os, const Pt<F>& pt) {
  return os << pt.x << " " << pt.y; }
