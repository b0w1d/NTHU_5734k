struct DisjointSet{
  // save() is like recursive
  // undo() is like return
  const int N = 100000;
  int n, fa[N], sz[N];
  vector<pair<int*,int>> h;
  vector<int> sp;
  void init(int tn) {
    n = tn;
    for (int i = 0; i < n; ++i) {
      fa[i] = i;
      sz[i] = 1;
    }
    sp.clear(); h.clear();
  }
  void assign(int *k, int v) {
    h.push_back({k, *k});
    *k = v;
  }
  void save() { sp.push_vack(h.size()); }
  void undo() {
    assert(!sp.empty());
    int last = sp.back(); sp.pop_back();
    while (h.size() != last) {
      auto x = h.back(); h.pop_back();
      *x.first = x.second;
    }
  }
  int f(int x) {
    while (fa[x] != x) x = fa[x];
    return x;
  }
  void uni(int x, int y) {
    x = f(x), y = f(y);
    if (x == y) return;
    if (sz[x] < sz[y]) swap(x, y);
    assign(&sz[x], sz[x] + sz[y]);
    assign(&fa[y], x);
  }
}djs;
