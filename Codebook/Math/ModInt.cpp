template <int mod>
struct ModInt {
  int val;
  int trim(int x) const { return x >= mod ? x - mod : x < 0 ? x + mod : x; }
  ModInt(int v = 0) : val(trim(v % mod)) {}
  ModInt(long long v) : val(trim(v % mod)) {}
  ModInt &operator=(int v) { return val = trim(v % mod), *this; }
  ModInt &operator=(const ModInt &oth) { return val = oth.val, *this; }
  ModInt operator+(const ModInt &oth) const { return trim(val + oth.val); }
  ModInt operator-(const ModInt &oth) const { return trim(val - oth.val); }
  ModInt operator*(const ModInt &oth) const { return 1LL * val * oth.val % mod; }
  ModInt operator/(const ModInt &oth) const {
    function<int(int, int, int, int)> modinv = [&](int a, int b, int x, int y) {
      if (b == 0) return trim(x);
      return modinv(b, a - a / b * b, y, x - a / b * y);
    };
    return *this * modinv(oth.val, mod, 1, 0);
  }
  bool operator==(const ModInt &oth) const { return val == oth.val; }
  ModInt operator-() const { return trim(mod - val); }
  template<typename T> ModInt pow(T pw) {
    bool sgn = false;
    if (pw < 0) pw = -pw, sgn = true;
    ModInt ans = 1;
    for (ModInt cur = val; pw; pw >>= 1, cur = cur * cur) {
      if (pw&1) ans = ans * cur;
    }
    return sgn ? ModInt{1} / ans : ans;
  }
};
