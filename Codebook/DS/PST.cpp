constexpr int PST_MAX_NODES = 1 << 22; // recommended: prepare at least 4nlgn, n to power of 2
struct Pst {
  int maxv;
  Pst *lc, *rc;
  Pst() : lc(nullptr), rc(nullptr), maxv(0) {}
  Pst(const Pst *rhs) : lc(rhs->lc), rc(rhs->rc), maxv(rhs->maxv) {}
  static Pst *build(int lb, int rb) {
    Pst *t = new(mem_ptr++) Pst;
    if (rb - lb == 1) return t;
    t->lc = build(lb, lb + rb >> 1);
    t->rc = build(lb + rb >> 1, rb);
    return t;
  }
  static int query(Pst *t, int lb, int rb, int ql, int qr) {
    if (qr <= lb || rb <= ql) return 0;
    if (ql <= lb && rb <= qr) return t->maxv;
    int mb = lb + rb >> 1;
    return max(query(t->lc, lb, mb, ql, qr), query(t->rc, mb, rb, ql, qr));
  }
  static Pst *modify(Pst *t, int lb, int rb, int k, int v) {
    Pst *n = new(mem_ptr++) Pst(t);
    if (rb - lb == 1) return n->maxv = v, n;
    int mb = lb + rb >> 1;
    if (k < mb) n->lc = modify(t->lc, lb, mb, k, v);
    else n->rc = modify(t->rc, mb, rb, k, v);
    n->maxv = max(n->lc->maxv, n->rc->maxv);
    return n;
  }
  static Pst mem_pool[PST_MAX_NODES];
  static Pst *mem_ptr;
  static void clear() {
    while (mem_ptr != mem_pool) (--mem_ptr)->~Pst();
  }
} Pst::mem_pool[PST_MAX_NODES], *Pst::mem_ptr = Pst::mem_pool;
/*
Usage:

vector<Pst *> version(N + 1);
version[0] = Pst::build(0, C); // [0, C)
for (int i = 0; i < N; ++i) version[i + 1] = modify(version[i], ...);
Pst::query(...);
Pst::clear();

*/
