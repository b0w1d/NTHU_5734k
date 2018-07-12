struct diameter_solver{
  vector<int> g[200000], d;
  int n;
  void init(int _n) {
    n = _n;
    d.resize(n);
  }
  void add_edge(int v, int u) { // 0-index
    g[v].push_back(u), g[u].push_back(v);
  }
  void dfs(int v = 0, int p = -1, int h = 0) {
    d[v] = h;
    for (int u: g[v]) if (p != u) dfs(u, v, h + 1);
  }
  int diameter() {
    dfs();
    int v = max_element(d.begin(), d.end()) - d.begin();
    dfs(v);
    return *max_element(d.begin(), d.end());
  }
}solver;
