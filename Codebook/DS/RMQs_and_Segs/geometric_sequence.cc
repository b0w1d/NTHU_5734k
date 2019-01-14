class Seg {
  int a, x; // tag, fixed x
  int l, m, r;
  int sum;
  Seg* ch[2];
  int size() { return r - l; }
  void modAdd(int &a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
  }
  int calc(int a) {
    if (x == 1) return 1ll * a * size() % MOD;
    return 1ll * a * (powM(x, size()) - 1) % MOD * inv(x - 1) % MOD;
    // It's recommend to build a table for inv and powM(x, .)
  }
  void pull() { 
    sum = ch[0]->sum + ch[1]->sum;
    if (sum >= MOD) sum -= MOD;
  }
  void push() { 
    if (a) {
      for (int i = 0; i < 2; ++i) {
        int na = 1ll * a * powM(x, i? ch[0]->size() : 0) % MOD;
        modAdd(ch[i]->a, na);
        modAdd(ch[i]->sum, ch[i]->calc(na));
      }
      a = 0;
    }
  }
public:
  Seg(int l, int r, long long x) : l(l), r(r), m(l + r >> 1), x(x), a(0) {
    if (r - l == 1) sum = 0;
    else {
      ch[0] = new Seg(l, m, x);
      ch[1] = new Seg(m, r, x);
      pull();
    }
  }
  void add(int ql, int qr, long long qa) { // add qa on ql
    if (ql <= l and r <= qr) {
      modAdd(a, qa);
      modAdd(sum, calc(qa));
    }
    else {
      push();
      if (ql < m) ch[0]->add(ql, qr, qa);
      if (m < qr) {
        if (ql < m) ch[1]->add(m, qr, qa * powM(x, m - ql) % MOD);
        else ch[1]->add(ql, qr, qa);
      }
      pull();
    }
  }
  int query(int ql, int qr) {
    if (ql <= l and r <= qr) return sum;
    int ans = 0;
    push();
    if (ql < m) modAdd(ans, ch[0]->query(ql, qr));
    if (m < qr) modAdd(ans, ch[1]->query(ql, qr));
    pull();
    return ans;
  }
};
