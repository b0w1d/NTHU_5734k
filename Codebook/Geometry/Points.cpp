template <typename T>
struct Pt {
  T x, y;
  Pt() : x(0), y(0) {}
  Pt(const T x, const T y) : x(x), y(y) {}
  template <class F> explicit operator Pt<F> () const {
    return Pt<F>((F)x, (F)y); }

  Pt operator+(const Pt b) const { return Pt(x + b.x, y + b.y); }
  Pt operator-(const Pt b) const { return Pt(x - b.x, y - b.y); }
  template <class F> Pt<F> operator* (const F fac) {
    return Pt<F>(x * fac, y * fac); }
  template <class F> Pt<F> operator/ (const F fac) {
    return Pt<F>(x / fac, y / fac); }

  T operator&(const Pt b) const { return x * b.x + y * b.y; }
  T operator^(const Pt b) const { return x * b.y - y * b.x; }

  bool operator==(const Pt b) const {
    return x == b.x and  y == b.y; }
  bool operator<(const Pt b) const {
    return x == b.x? y < b.y: x < b.x; }

  Pt operator-() const { return Pt(-x, -y); }
  T norm() const { return *this & *this; }
  Pt prep() const { return Pt(-y, x); }
};
template<class F> istream& operator>>(istream& is, Pt<F> &pt) {
  return is >> pt.x >> pt.y;
}
template<class F> ostream& operator<<(ostream& os, Pt<F> &pt) {
  return os << pt.x << ' ' << pt.y;
}
