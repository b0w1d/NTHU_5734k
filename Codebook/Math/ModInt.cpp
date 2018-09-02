template <int mod>
struct ModInt {
  int val;
  ModInt(int v = 0) : val((v % mod + mod) % mod) {}
  ModInt(long long v) : val((v % mod + mod) % mod) {}
  ModInt &operator=(int v) { return val = (v % mod + mod) % mod, *this; }
  ModInt &operator=(const ModInt &oth) { return val = oth.val, *this; }
  ModInt operator+(const ModInt &oth) const {
    int u = (val + oth.val) % mod;
    return u < 0 ? u + mod : u;
  }
  ModInt operator-(const ModInt &oth) const {
    int u = (val - oth.val) % mod;
    return u < 0 ? u + mod : u;
  }
  ModInt operator*(const ModInt &oth) const {
    return 1LL * val * oth.val % mod;
  }
  ModInt operator/(const ModInt &oth) const {
    function<int(int, int, int, int)> modinv = [&](int a, int b, int x, int y) {
      if (b == 0) return x < 0 ? x + mod : x;
      return modinv(b, a - a / b * b, y, x - a / b * y);
    };
    return *this * modinv(oth.val, mod, 1, 0);
  }
  ModInt operator-() const { return mod - val; }
};
