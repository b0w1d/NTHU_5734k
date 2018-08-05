struct topological_sort {
  vector<vector<int>> g;
  vector<int> finish;
  vector<bool> vis;
  int n;
  void init(int _n) {
    n = _n;
    g.assign(n, vector<int>(0));
    finish.resize(n);
    vis.assign(n, false);
  }
  void add_edge(int u, int v) {
    g[u].push_back(v);
  }
  void dfs(int v) {
    static int timer = 0;
    vis[v] = true;
    for (int u: g[v])
      if (not vis[u]) dfs(u);
    finish[v] = timer++;
  }
  vector<int> make_sort() {
    vector<int> P(n);
    for (int i = 0; i < n; ++i) {
      P[i] = i;
      if (not vis[i]) dfs(i);
    }
    sort(P.begin(), P.end(), [&](int v, int u) { return finish[v] > finish[u]; });
    return P;
  }
} sorter;
