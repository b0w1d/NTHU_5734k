template<typename F = long long>
struct Linear { // y = a * x + b;
  F a, b;
  Linear(F a = 0, F b = 0) : a(a), b(b) {}
  bool operator<(Linear oth) const {
    return a == oth.a ? b < oth.b : a < oth.a;
  }
  template<typename T> T operator()(T x) const { return a * x + b; }
};

template<typename F = long long>
class ConvexHull { // lower envelop
  vector<Linear<F>> f;
  bool cross(Linear<F> P, Linear<F> Q, Linear<F> T) const {
    if (Q.a == T.a) return Q.b <= T.b;
    auto ceil2 = [=](F a, F b) {
      return a >= 0 ? (a + b - 1) / b : a / b;
    };
    const F x = ceil2(P.b - Q.b, Q.a - P.a);
    const F y = ceil2(Q.b - T.b, T.a - Q.a);
    return y <= x;
  }
  void getHull() {
    int m = 0;
    for (int i = 0; i < f.size(); ++i) {
      while (m >= 2 and cross(f[m - 2], f[m - 1], f[i]))  --m;
      if (m == 1 and f[0].a == f[i].a) --m;
      f[m++] = f[i];
    }
    f.resize(m);
  }
public:
  int size() const { return f.size(); }
  ConvexHull(vector<Linear<F>> A) : f(A) {
    sort(f.begin(), f.end());
    getHull();
  }
  F operator()(F x) const {
    int n = f.size();
    auto df = [&](int i) { return f[i + 1](x) - f[i](x); };
    if (n == 0) return numeric_limits<F>::min();
    if (n == 1 or df(0) <= 0) return f[0](x);
    int l = 0, r = n - 1;
    while (r - l > 1) {
      int m = l + r >> 1;
      (df(m) < 0 ? r : l) = m;
    }
    return f[r](x);
  }
  void merge(const ConvexHull &oth) {
    auto mid = f.size();
    f.insert(f.end(), oth.f.begin(), oth.f.end());
    inplace_merge(f.begin(), f.begin() + mid, f.end());
    getHull();
  }
};

template<typename F>
class ExpandableHull {
  vector<ConvexHull<F>> stk;
public:
  void addLine(Linear<F> l) {
    stk.emplace_back(vector<Linear<F>>{l});
    int m = stk.size();
    while (m > 1 and stk[m - 2].size() <= stk[m - 1].size()) {
      stk[m - 2].merge(stk[m - 1]);
      stk.pop_back();
      --m;
    }
  }
  F operator()(F x) {
    return accumulate(stk.begin(), stk.end(), numeric_limits<F>::min(),
      [&](F y, ConvexHull<F>& C) { return max(y, C(x)); 
    });
  }
};
