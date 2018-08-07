struct k_colorable{
  vector<int> g[100], color;
  int n;
  void init(int _n) {
    assert(_n);
    n = _n, color.assign(n, 0);
    for_each(g, g + n, [](vector<int> &g) { g.clear(); });
    color[0] = 1; // may assume color[0] = 1
  }
  void add_edge(int v, int u) {
    g[v].push_back(u), g[u].push_back(v);
  }
  bool colorable(int k, int v = 1) {
    if (v == n) return true;
    int used = 0;
    for (int u: g[v]) {
      if (color[u]) used |= 1 << (color[u] - 1);
    }
    for (int c = 0; c < k; ++c) {
      if (((used >> c)&1) == 0) {
        color[v] = c + 1;
        if (colorable(k, v + 1)) return true;
        color[v] = 0;
      }
    }
    return false;
  }
} graph;
