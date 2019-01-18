/* p == (a << n) + 1, g = pow(root, (p - 1) / n)
   n    1 << n      p          a    root
   5    32          97         3    5
   6    64          193        3    5
   7    128         257        2    3
   8    256         257        1    3
   9    512         7681       15   17
   10   1024        12289      12   11
   11   2048        12289      6    11
   12   4096        12289      3    11
   13   8192        40961      5    3
   14   16384       65537      4    3
   15   32768       65537      2    3
   16   65536       65537      1    3
   17   131072      786433     6    10
   18   262144      786433     3    10 (605028353, 2308, 3)
   19   524288      5767169    11   3
   20   1048576     7340033    7    3
   20   1048576     998244353  952  3
   21   2097152     23068673   11   3
   22   4194304     104857601  25   3
   23   8388608     167772161  20   3
   24   16777216    167772161  10   3
   25   33554432    167772161  5    3 (1107296257, 33, 10)
   26   67108864    469762049  7    3
*/
class Polynomial {
  vector<int> P;
  int R, M, A; // root, mod, a
  int lg, n;
  bool isPointValue = false;
  inline void trim(int &a) { if (a >= M) a -= M; }
  inline void modAdd(int &a, int b) { a += b; trim(a);}
  int powM(int x, long long b) {
    int s = 1, m = x;
    for (; b; m = 1ll * m * m % M, b >>= 1)
      if (b&1) s = 1ll * s * m % M;
    return s;
  }
  int discreteSqrt(int x) {
    for (int i = 1; i <= M; ++i) if (i * i == x) return i;
    assert(0);
  }
  void bitReverse() {
    for (int j = 1, i = 0; j < n - 1; ++j) {
      for (int k = n >> 1; k > (i ^= k); k >>= 1);
      if (j < i) swap(P[i], P[j]);
    } //bit reverse
  }
public:
  Polynomial(vector<int> P, int M = 998244353, int R = 3) :
  P(P), M(M), R(R) { isPointValue = false; resize(P.size()); }
  void NTT(bool inv = 0) {
    assert(isPointValue == inv);
    bitReverse();
    const int G = powM(R, 1ll * A * (inv? M - 2: 1) % (M - 1)); // order is 1<<lg
    for (int i = 0; i <= lg; ++i) {
      const int W = powM(G, 1<<(lg - i)); // order is 1<<i
      for (int k = 0; k < (1<<lg); k += 1 << i) {
        int B = 1;
        for (int j = 0; j < (1 << i - 1); ++j, B = 1ll * B * W % M) {
          int t = 1ll * B * P[k + j + (1 << i - 1)] % M;
          int u = P[k + j];
          trim(P[k + j] = u + t);
          trim(P[k + j + (1 << i - 1)] = u - t + M);
        }
      }
    }
    if (inv) {
      const int invN = powM(n, M - 2);
      transform(P.begin(), P.end(), P.begin(), [=](int a) {
        return 1ll * a * invN % M;
      });
    }
    isPointValue = not isPointValue;
  }
  void setPointValue() { if (not isPointValue) NTT(); }
  void setCoefficient() { if (isPointValue) NTT(true); }
  int degree() {
    setCoefficient();
    return n - 1 - (find_if(P.rbegin(), P.rend(), [](int a) {
      return a != 0; }) - P.rbegin());
  }
  void resize(int _n) {
    setCoefficient();
    n = _n, lg = 31 - __builtin_clz(n);
    assert(__builtin_popcount(n) == 1);
    P.resize(n), A = (M - 1) / n;
  }
  int& operator[](size_t i) {
    setCoefficient();
    return P[i];
  }
  Polynomial& operator^=(long long k) {
    setPointValue();
    for (int i = 0; i < n; ++i) P[i] = powM(P[i], k);
    return *this;
  }
  Polynomial& operator=(Polynomial oth) {
    P = oth.P, R = oth.R, M = oth.M, A = oth.A, lg = oth.lg, A = oth.A;
    isPointValue = oth.isPointValue;
    return *this;
  }
  Polynomial& operator+=(Polynomial oth) {
    assert(oth.n == n);
    if (isPointValue != oth.isPointValue) oth.NTT(oth.isPointValue);
    for (int i = 0; i < n; ++i) trim(P[i] += oth[i]);
    return *this;
  }
  Polynomial operator+(Polynomial oth) {
    Polynomial cp = *this;
    return cp += oth;
  }
  Polynomial& operator+=(int k) {
    setCoefficient();
    trim(P[0] += k);
    return *this;
  }
  Polynomial operator+(int k) {
    Polynomial cp = *this;
    return cp += k;
  }
  Polynomial& operator*=(Polynomial oth) {
    assert(oth.n == n);
    bool overFlow = degree() + oth.degree() >= n;
    if (overFlow) oth.resize(2 * n), resize(2 * n);
    oth.setPointValue();
    setPointValue();
    for (int i = 0; i < n; ++i) P[i] = 1ll * P[i] * oth.P[i] % M;
    if (overFlow)
      resize(n / 2), cerr << "Multiplication OverFlow, result modded by x^n\n";
    return *this;
  }
  Polynomial operator*(Polynomial oth) {
    Polynomial cp = *this;
    return cp *= oth;
  }
  Polynomial& operator*=(int k) {
    for (int i = 0; i < n; ++i) P[i] = 1ll * P[i] * k % M;
    return *this;
  }
  Polynomial operator*(int k) {
    Polynomial cp = *this;
    return cp *= k;
  }
  Polynomial inverse() { // mod x^n
    setCoefficient();
    Polynomial h({powM(P[0], M - 2)}, M, R);
    for (int i = 1; i <= lg; ++i) {
      Polynomial curF(vector<int>(P.begin(), P.begin() + (1<<i)), M, R);
      h.resize(4<<i); fill(h.P.begin() + (1<<i), h.P.end(), 0);
      curF.resize(4<<i);
      h.setPointValue();
      curF.setPointValue();
      for (int j = 0; j < (4<<i); ++j)
        trim(h.P[j] = (2ll * h.P[j] - 1ll * h.P[j] * h.P[j] % M * curF.P[j]) % M + M);
    }
    h.resize(n);
    return h;
  }
  Polynomial sqrt() { // mod x^n
    setCoefficient();
    Polynomial h({discreteSqrt(P[0]), 0}, M, R);
    for (int i = 1; i <= lg; ++i) {
      h.resize(2<<i);
      Polynomial curF(vector<int>(P.begin(), P.begin() + (1<<i)), M, R);
      curF.resize(2<<i);
      h = (h + curF * h.inverse()) * powM(2, M - 2);
    }
    h.resize(n);
    return h;
  }
};
