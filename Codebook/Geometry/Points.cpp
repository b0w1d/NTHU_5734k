template <class F>
struct Pt {
  F x, y;
  Pt() : x(0), y(0) {}
  Pt(const F x, const F y) : x(x), y(y) {}

  template <class F1> explicit operator Pt<F1> () const {
    return Pt<F1>(static_cast<F1>(x), static_cast<F1>(y)); }
  template <class F1> Pt operator + (const Pt<F1> oth) {
    return Pt<F1>(x + oth.x, y + oth.y); }
  template <class F1> Pt operator - (const Pt<F1> oth) {
    return Pt<F1>(x - oth.x, y - oth.y); }
  template <class F1> Pt operator * (const F1 fac) {
    return Pt<F1>(x * fac, y * fac); }
  template <class F1> Pt operator / (const F1 fac) {
    return Pt<F1>(x / fac, y / fac); }
  template <class F1> F1 operator & (const Pt<F1> oth) {
    return static_cast<F1>(x * oth.x + y * oth.y); }
  template <class F1> F1 operator ^ (const Pt<F1> oth) {
    return static_cast<F1>(x * oth.y - y * oth.x); }

  template <class F1> Pt& operator = (const Pt<F1> oth) {
    return *this = (Pt<F1>) oth; }
  template <class F1> Pt& operator += (const Pt<F1> oth) {
    return *this = *this + oth; }
  template <class F1> Pt& operator -= (const Pt<F1> oth) {
    return *this = *this - oth; }
  template <class F1> Pt& operator *= (const F1 fac) {
    return *this = *this * fac; }
  template <class F1> Pt& operator /= (const F1 fac) {
    return *this = *this / fac; }
};
