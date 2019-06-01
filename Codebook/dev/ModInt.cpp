template <int mod>
struct ModInt {
  static int normal(int v) { return v < mod ? 0 <= v ? v : v + mod : v - mod; }
  int val;
  ModInt(int v = 0) : val(normal(v)) {}
  ModInt(int64_t v) : val(normal(v % mod)) {}
  ModInt operator+(const ModInt &b) const { return normal(val + b.val); }
  ModInt operator-(const ModInt &b) const { return normal(val - b.val); }
  ModInt operator*(const ModInt &b) const { return 1LL * val * b.val % mod; }
  ModInt operator/(const ModInt &oth) const {
    function<int(int, int, int, int)> modinv = [&](int a, int b, int x, int y) {
      if (b == 0) return x < 0 ? x + mod : x;
      return modinv(b, a - a / b * b, y, x - a / b * y);
    };
    return *this * modinv(oth.val, mod, 1, 0);
  }
  ModInt operator-() const { return mod - val; }
  template<int _mod>
  friend ostream& operator<<(ostream& os, ModInt<_mod> m) { return os << m.val, os; }
};
