struct Seg{
  int l, m, r, min_value = 1e9;
  Seg* ch[2] = {nullptr, nullptr};
  Seg(int l, int r) : l(l), r(r) {
    m = l + r >> 1;
  }
  void build() {
    if (r - l == 1) return;
    ch[0] = new Seg(l, m);
    ch[1] = new Seg(m, r);
    ch[0] -> build();
    ch[1] -> build();
  }
  Seg* modify(int p, int v) {
    Seg* ret = new Seg(l, r);
    if (r - l == 1) {
      ret -> min_value = v;
      return ret;
    }
    ret -> ch[0] = p < m ? ch[0] -> modify(p, v) : ch[0];
    ret -> ch[1] = p >= m ? ch[1] -> modify(p, v) : ch[1];
    return ret;
  }
  int query(int ql, int qr) {
    if (r - l == 1) return min_value;
    int ans = 1e9;
    if (ql < m) ans = min(ans, ch[0] -> query(ql, qr));
    if (qr > m) ans = min(ans, ch[1] -> query(ql, qr));
    return ans;
  }
};
