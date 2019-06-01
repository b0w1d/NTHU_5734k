struct Ftree {
  int dat[1 << 20];
  void add(int ql, int qr, int v) { // [ql, qr)
    for (int i = ql + 1; i < 1 << 20; i += i & -i) dat[i] += v;
    for (int i = qr + 1; i < 1 << 20; i += i & -i) dat[i] -= v;
  }
  int query(int k) {
    int r = 0;
    for (int i = k + 1; i; i -= i & -i) r += dat[i];
    return r;
  }
};