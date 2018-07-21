struct seg{
  LL sum = 0, lazy = 0;
  seg* ch[2] = {nullptr, nullptr};
  int l, r, m;
  seg(int l, int r) : l(l), r(r) {
    if (r - l > 1) {
      m = l + r >> 1;
      ch[0] = new seg(l, m);
      ch[1] = new seg(m, r);
    }
  }
  void reset() {
    sum = lazy = 0;
    if (r - l > 1) ch[0] -> reset(), ch[1] -> reset();
  }
  void push() {
    if (r - l > 1) for (int i = 0; i < 2; ++i)
      ch[i] -> sum += lazy * (ch[i] -> r - ch[i] -> l),
      ch[i] -> lazy += lazy;
    lazy = 0;
  }
  void pull() {
    sum = ch[0] -> sum + ch[1] -> sum;
  }
  void add(int L, int R, LL val) {
    if (L <= l and r <= R)
      return sum += val * (r - l), lazy += val, void();
    else {
      push();
      if (L < m) ch[0] -> add(L, R, val);
      if (m < R) ch[1] -> add(L, R, val);
      pull();
    }
  }
  LL query(int L, int R) {
    if (L <= l and r <= R) return sum;
    push();
    LL ans = 0;
    if (L < m) ans += ch[0] -> query(L, R);
    if (m < R) ans += ch[1] -> query(L, R);
    return ans;
  }
} *root;
