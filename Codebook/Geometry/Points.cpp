template <typename T>
struct Pt {
  T x, y;
  Pt() : x(0), y(0) {}
  Pt(const T x, const T y) : x(x), y(y) {}
  template <class F> operator Pt<F> () const {
    return Pt<F>(static_cast<F>(x), static_cast<F>(y)); }
  Pt& operator=(const Pt b) { return *this = b; }
  Pt operator+(const Pt b) const { return Pt(x + b.x, y + b.y); }
  Pt operator-(const Pt b) const { return Pt(x - b.x, y - b.y); }
  Pt operator*(const T b) const { return Pt(x * b, y * b); }
  template <class F> Pt<F> operator* (const F fac) {
    return Pt<F>(x * fac, y * fac); }
  template <class F> Pt<F> operator/ (const F fac) {
    return Pt<F>(x / fac, y / fac); }
  Pt operator/(const T b) const { return Pt(x / b, y / b); }
  T operator&(const Pt b) const { return x * b.x + y * b.y; }
  T operator^(const Pt b) const { return x * b.y - y * b.x; }
  bool operator==(const Pt b) const { return x == b.x && y == b.y; }

  Pt prep() const { return Pt(-y, x); }
  T norm2() const { return *this & *this; }
  double rad() const { return atan2(x, y); }

  Pt& operator+=(const Pt b) { return *this = *this + b; }
  Pt& operator-=(const Pt b) { return *this = *this - b; }
  Pt& operator*=(const T fac) { return *this = *this * fac; }
  Pt& operator/=(const T fac) { return *this = *this / fac; }
};
