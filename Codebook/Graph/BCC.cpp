struct BCC_solver{
  vector<vector<int>> g, BCC; // BCC are the components
  vector<int> dfn, low, stk;
  int step = 0;
  void init(int n) {
    g.assign(n, vector<int>(0)), BCC.clear();
    stk.clear(), step = 0;
    dfn.assign(n, -1), low.assign(n, -1);
  }
  void add_edge(int a, int b) { g[a].push_back(b), g[b].push_back(a); }
  void dfs(int u, int p = -1) {
    dfn[u] = low[u] = step++;
    stk.push_back(u);
    for (int v: g[u]) {
      if (v == p) continue;
      if (dfn[v] == -1) {
        dfs(v, u);
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
  vector<vector<int>> find_BCC() {
    dfs(0);
    return BCC;
  }
}bcc_solver;
