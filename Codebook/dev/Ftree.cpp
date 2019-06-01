template<typename D, D zero>
struct Ftree {
  vector<D> dat;
  function<D(D, D)> fadd;
  Ftree(int n, function<D(D, D)> f) : dat(n + 1), fadd(f) {}
  D operator()(int x) {
    D s(zero);
    for (int i = x + 1; i; i -= i & -i) s = fadd(s, dat[i]);
    return s;
  }
  void add(int x, const D &v) {
    for (int i = x + 1; i < dat.size(); i += i & -i) dat[i] = fadd(dat[i], v);
  }
};
