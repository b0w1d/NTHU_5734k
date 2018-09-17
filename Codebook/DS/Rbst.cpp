constexpr int RBST_MAX_NODES = 1 << 20;
struct Rbst {
  int size, val;
  // int minv;
  // int add_tag, rev_tag;
  Rbst *lc, *rc;
  Rbst(int v = 0) : size(1), val(v), lc(nullptr), rc(nullptr) {
    // minv = v;
    // add_tag = 0;
    // rev_tag = 0;
  }
  void push() {
    /*
    if (add_tag) { // unprocessed subtree has tag on root
      val += add_tag;
      minv += add_tag;
      if (lc) lc->add_tag += add_tag;
      if (rc) rc->add_tag += add_tag;
      add_tag = 0;
    }
    if (rev_tag) {
      swap(lc, rc);
      if (lc) lc->rev_tag ^= 1;
      if (rc) rc->rev_tag ^= 1;
      rev_tag = 0;
    }
    */
  }
  void pull() {
    size = 1;
    // minv = val;
    if (lc) {
      lc->push();
      size += lc->size;
      // minv = min(minv, lc->minv);
    }
    if (rc) {
      rc->push();
      size += rc->size;
      // minv = min(minv, rc->minv);
    }
  }
  static int get_size(Rbst *t) { return t ? t->size : 0; }
  static void split(Rbst *t, int k, Rbst *&a, Rbst *&b) {
    if (!t) return void(a = b = nullptr);
    t->push();
    if (get_size(t->lc) >= k) {
      b = t;
      split(t->lc, k, a, b->lc);
      b->pull();
    } else {
      a = t;
      split(t->rc, k - get_size(t->lc) - 1, a->rc, b);
      a->pull();
    }
  } // splits t, left k elements to a, others to b, maintaining order
  static Rbst *merge(Rbst *a, Rbst *b) {
    if (!a || !b) return a ? a : b;
    if (rand() % (a->size + b->size) < a->size) {
      a->push();
      a->rc = merge(a->rc, b);
      a->pull();
      return a;
    } else {
      b->push();
      b->lc = merge(a, b->lc);
      b->pull();
      return b;
    }
  } // merges a and b, maintaing order
  static int lower_bound(Rbst *t, const int &key) {
    if (!t) return 0;
    if (t->val >= key) return lower_bound(t->lc, key);
    return get_size(t->lc) + 1 + lower_bound(t->rc, key);
  }
  static void insert(Rbst *&t, const int &key) {
    int idx = lower_bound(t, key);
    Rbst *tt;
    split(t, idx, tt, t);
    t = merge(merge(tt, new(mem_ptr++) Rbst(key)), t);
  }

  static Rbst mem_pool[RBST_MAX_NODES]; // CAUTION!!
  static Rbst *mem_ptr;
  static void clear() {
    while (mem_ptr != mem_pool) (--mem_ptr)->~Rbst();
  }
} Rbst::mem_pool[RBST_MAX_NODES], *Rbst::mem_ptr = Rbst::mem_pool;

/*
Usage:

Rbst *t = new(Rbst::mem_ptr++) Rbst(val);
t = Rbst::merge(t, new(Rbst::mem_ptr++) Rbst(another_val));
Rbst *a, *b;
Rbst::split(t, 2, a, b); // a will have first 2 elements, b will have the rest, in order
Rbst::clear(); // wipes out all memory; if you know the mechanism of clear() you can maintain many trees

*/
