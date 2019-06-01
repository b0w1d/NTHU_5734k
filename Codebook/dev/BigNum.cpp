struct BigNum {
  typedef long long ll;
  int sign;
  ll B;    // TODO: assert(N * B * B < LL_LIMIT) if mul is used
  int BW;  // base width
  vector<ll> cells;
  BigNum(string s = "0", ll b = 10000) : sign(1), B(b), BW(ceil(log10(b))) {
    if (s[0] == '-') sign = -1, s = s.substr(1);
    cells.resize((s.size() + BW - 1) / BW);
    for (int i = 0; i < cells.size(); ++i) {
      int lb = max(0, int(s.size()) - (i + 1) * BW);
      int len = min(BW, int(s.size()) - i * BW);
      cells[i] = stoi(s.substr(lb, len));
    }
  }
  BigNum(const vector<ll> &v, ll b = 10000)
      : sign(1), B(b), BW(ceil(log10(b))), cells(v) {}
  friend bool operator<(const BigNum &a, const BigNum &b) {
    if (a.sign != b.sign) return a.sign < b.sign;
    if (a.cells.size() != b.cells.size())
      return a.cells.size() < b.cells.size();
    for (int i = a.cells.size() - 1; ~i; --i)
      if (a.cells[i] != b.cells[i]) return a.cells[i] < b.cells[i];
    return false;
  }
  friend bool operator==(const BigNum &a, const BigNum &b) {
    return a.sign == b.sign && a.cells == b.cells;
  }
  friend bool operator!=(const BigNum &a, const BigNum &b) { return !(a == b); }
  friend bool operator<=(const BigNum &a, const BigNum &b) { return !(b < a); }
  friend bool operator>(const BigNum &a, const BigNum &b) { return b < a; }
  friend bool operator>=(const BigNum &a, const BigNum &b) { return !(a < b); }
  BigNum &normal(int result_sign = 1) {
    ll c = 0;
    for (int i = 0; i < cells.size(); ++i) {
      if (cells[i] < 0) {
        if (i + 1 == cells.size()) cells.emplace_back(0);
        ll u = (abs(cells[i]) + B - 1) / B;
        cells[i + 1] -= u;
        cells[i] += u * B;
      }
      ll u = cells[i] + c;
      cells[i] = u % B;
      c = u / B;
    }
    for (; c; c /= B) cells.emplace_back(c % B);
    while (cells.size() > 1 && cells.back() == 0) cells.pop_back();
    sign = result_sign;
    return *this;
  }
  static vector<ll> add(const vector<ll> &a, const vector<ll> &b, int al = -1,
                        int ar = -1, int bl = -1, int br = -1) {
    if (al == -1) al = 0, ar = a.size(), bl = 0, br = b.size();
    vector<ll> c(max(ar - al, br - bl));
    for (int i = 0; i < c.size(); ++i)
      c[i] = (al + i < a.size() ? a[al + i] : 0) +
             (bl + i < b.size() ? b[bl + i] : 0);
    return c;
  }
  static vector<ll> sub(const vector<ll> &a, const vector<ll> &b, int al = -1,
                        int ar = -1, int bl = -1, int br = -1) {
    if (al == -1) al = 0, ar = a.size(), bl = 0, br = b.size();
    vector<ll> c(max(ar - al, br - bl));
    for (int i = 0; i < c.size(); ++i)
      c[i] = (al + i < a.size() ? a[al + i] : 0) -
             (bl + i < b.size() ? b[bl + i] : 0);
    return c;
  }
  static vector<ll> cat_zero(const vector<ll> &a, int k) {
    vector<ll> b(a.size() + k);
    for (int i = 0; i < a.size(); ++i) b[k + i] = a[i];
    return b;
  }
  friend BigNum operator+(BigNum x, BigNum y) {
    if (x.sign == y.sign) return BigNum(add(x.cells, y.cells)).normal();
    if (x.sign == -1) swap(x, y);
    y.sign = 1;
    if (x >= y) return BigNum(sub(x.cells, y.cells)).normal();
    return BigNum(sub(y.cells, x.cells)).normal(-1);
  }
  friend BigNum operator-(BigNum x, BigNum y) {
    y.sign *= -1;
    return x + y;
  }
  friend BigNum operator*(BigNum x, BigNum y) {
    if (x.cells.size() < y.cells.size()) swap(x, y);
    int nn = 31 - __builtin_clz(int(x.cells.size())) +
             (__builtin_popcount(int(x.cells.size())) > 1);
    function<vector<ll>(const vector<ll> &, const vector<ll> &, int, int, int,
                        int)>
        karatsuba = [&](const vector<ll> &a, const vector<ll> &b, int al,
                        int ar, int bl, int br) {
          if (al + 256 >= ar) {
            vector<ll> r(ar - al << 1);
            for (int i = 0; i < ar - al; ++i)
              for (int j = 0; j < br - bl; ++j)
                r[i + j] += a[al + i] * b[bl + j];
            return r;
          }
          vector<ll> z1 = karatsuba(a, b, al + ar >> 1, ar, bl + br >> 1, br);
          vector<ll> z2 = karatsuba(a, b, al, al + ar >> 1, bl, bl + br >> 1);
          vector<ll> p = cat_zero(z1, ar - al);
          vector<ll> a12 = add(a, a, al, al + ar >> 1, al + ar >> 1, ar);
          vector<ll> b12 = add(b, b, bl, bl + br >> 1, bl + br >> 1, br);
          vector<ll> ab12 = karatsuba(a12, b12, 0, a12.size(), 0, b12.size());
          vector<ll> q1 = sub(ab12, z1);
          vector<ll> q2 = sub(q1, z2);
          vector<ll> q = cat_zero(q2, ar - al >> 1);
          vector<ll> r1 = add(p, q);
          vector<ll> r = add(r1, z2);
          return r;
        };
    x.cells.resize(1 << nn);
    y.cells.resize(1 << nn);
    vector<ll> k = karatsuba(x.cells, y.cells, 0, 1 << nn, 0, 1 << nn);
    return BigNum(k).normal(x.sign * y.sign);
  }
  friend ostream &operator<<(ostream &os, BigNum x) {
    if (x.sign == -1) os << '-';
    for (auto it = x.cells.rbegin(); it != x.cells.rend(); ++it) {
      if (it == x.cells.rbegin())
        os << *it;
      else
        os << setw(x.BW) << setfill('0') << *it;
    }
    return os;
  }
  friend istream &operator>>(istream &is, BigNum &x) {
    string s;
    is >> s;
    x = BigNum(s);
    return is;
  }
};
