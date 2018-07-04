struct Seg{
  pii val;
  Seg *l, *r;
  Seg() : val({INF, 0}), l(NULL), r(NULL) {}
  Seg(Seg* l, Seg* r) : l(l), r(r) {
    val = min(l -> val, r -> val);
  }
  Seg(int pos, int val) : l(NULL), r(NULL) {
    this -> val = {val, pos};
  }
};
pii query(Seg* t, int l, int r, int L, int R) {
  if (L >= R) return {INF, 0};
  if (L <= l and r <= R) return t -> val;
  int mid = l + r >> 1;
  return min(query(t -> l, l, mid, L, min(mid, R)), 
             query(t -> r, mid, r, max(mid, L), R));
}
Seg* modify(Seg* t, int l, int r, int pos, int val) {
  if (r - l == 1) return new Seg(pos, val);
  int m = l + r >> 1;
  if (pos < m) return new Seg(modify(t -> l, l, m, pos, val), t -> r);
  else return new Seg(t -> l, modify(t -> r, m, r, pos, val));
}
Seg* build(int l, int r) {
  if (l == r - 1) return new Seg(l, INF);
  else {
    int mid = l + r >> 1;
    return new Seg(build(l, mid), build(mid, r));
  }
}
