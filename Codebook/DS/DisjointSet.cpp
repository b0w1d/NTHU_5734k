struct DisjointSet{
  // save() is like recursive
  // undo() is like return
  int n;
  vector<int> fa, sz;
  vector<pair<int*,int>> h;
  vector<int> sp;
  void init(int tn) {
    n = tn, sz.assign(n, 1), fa.resize(n);
    for (int i = 0; i < n; ++i)
      fa[i] = i, sz[i] = 1;
    sp.clear(); h.clear();
  }
  void assign(int *k, int v) {
    h.push_back({k, *k});
    *k = v;
  }
  void save() { sp.push_back(h.size()); }
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
  bool uni(int x, int y) {
    x = f(x), y = f(y);
    if (x == y) return false;
    if (sz[x] < sz[y]) swap(x, y);
    assign(&sz[x], sz[x] + sz[y]);
    assign(&fa[y], x);
    return true;
  }
}djs;
