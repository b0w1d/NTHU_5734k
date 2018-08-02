struct BCC_solver{
  vector<vector<int>> g, BCC; // BCC are the BRIDGE/AC VERTICE components
  vector<int> dfn, low, stk;
  int n, step = 0;
  void init(int _n) {
    n = _n, step = 0;
    g.assign(n, vector<int>(0)), BCC.clear();
    stk.clear(), step = 0;
    dfn.assign(n, -1), low.assign(n, -1);
  }
  void add_edge(int a, int b) { g[a].push_back(b), g[b].push_back(a); }
  void dfs_bridge(int u, int p = -1) {
    dfn[u] = low[u] = step++;
    stk.push_back(u);
    for (int v: g[u]) {
      if (v == p) continue;
      if (dfn[v] == -1) {
        dfs_bridge(v, u);
        low[u] = min(low[u], low[v]);
      } else low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
      BCC.push_back(vector<int>(0));
      while (stk.back() != u)
        BCC.back().push_back(stk.back()),
        stk.pop_back();
      BCC.back().push_back(u);
      stk.pop_back();
    }
  }
  void dfs_vertice(int u, int p = -1) {
    dfn[u] = low[u] = step++;
    stk.push_back(u);
    int z; // if u root, check it's ch_sz
    for (int v: g[u]) {
      if (v == p) continue;
      if (dfn[v] == -1) {
        dfs_vertice(v, u);
        low[u] = min(low[u], low[v]);
        if (low[v] >= dfn[u]) { // u is acc
          BCC.push_back(vector<int>(0));
          do {
            z = stk.back(); stk.pop_back();
            BCC.back().push_back(z);
          } while (z != v);
          BCC.back().push_back(u);
        }
      } else low[u] = min(low[u], dfn[v]);
    }
  }
  vector<vector<int>> find_BCC() {
    for (int i = 0; i < n; ++i)
      if (dfn[i] == -1)
        dfs_vertice(i); //dfs_bridge(0);
    return BCC;
  }
}bcc_solver;
