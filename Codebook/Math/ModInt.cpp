template<int mod>
struct ModInt {
  int val;
  ModInt(int v = 0) : val((v % mod + mod) % mod) {}
  ModInt(long long v) : val((v % mod + mod) % mod) {}
  ModInt& operator=(const ModInt &oth) {
    return val = oth.val, *this;
  }
  ModInt operator+(const ModInt &oth) const {
    int u = val + oth.val;
    if (u < 0) u += mod;
    return u;
  }
  ModInt operator*(const ModInt &oth) const {
    return 1LL * val * oth.val % mod;
  }
  ModInt operator-() const {
    return val > 0 ? mod - val : 0;
  }
};
