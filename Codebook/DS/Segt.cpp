template<int n, typename E, typename T, typename FTE, typename FTT, typename FEE>
struct Segt {
  E ei;
  T ti;
  vector<E> dat;
  vector<T> tag;
  FTE fte;
  FTT ftt;
  FEE fee;
  Segt(E ei, T ti, FTE a, FTT b, FEE c) : ei(ei), ti(ti), fte(a), ftt(b), fee(c){
    dat.assign(2 * n, ei);
    tag.assign(2 * n, ti);
  }
  void build(vector<E> a) {
    for (int i = 0; i < a.size(); ++i) dat[n + i] = a[i];
    for (int i = n - 1; i; --i) dat[i] = fee(dat[i << 1], dat[i << 1 | 1]);
  }
  void push(int k) {
    for (int c = 0; c < 2; ++c) {
      tag[k << 1 | c] = ftt(tag[k], tag[k << 1 | c]);
      dat[k << 1 | c] = fte(tag[k], dat[k << 1 | c]);
    }
    tag[k] = ti;
  }
  void update(T t, int ql, int qr, int lb = 0, int rb = n, int k = 1) {
    if (qr <= lb || rb <= ql) return;
    if (ql <= lb && rb <= qr) {
      tag[k] = ftt(t, tag[k]);
      dat[k] = fte(t, dat[k]);
      return;
    }
    push(k);
    int mb = lb + rb >> 1;
    update(t, ql, qr, lb, mb, k << 1);
    update(t, ql, qr, mb, rb, k << 1 | 1);
    dat[k] = fee(dat[k << 1], dat[k << 1 | 1]);
  }
  E query(int ql, int qr, int lb = 0, int rb = n, int k = 1) {
    if (qr <= lb || rb <= ql) return ei;
    if (ql <= lb && rb <= qr) return dat[k];
    push(k);
    int mb = lb + rb >> 1;
    return fee(query(ql, qr, lb, mb, k << 1), query(ql, qr, mb, rb, k << 1 | 1));
  }
};
