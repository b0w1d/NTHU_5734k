const int SIZE = 1e6 + 10;
struct Tree_ecc{
  vector<pair<int, LL>> g[SIZE];
  LL dp[SIZE][2] = {0}, ecc[SIZE];
  int n = -1;
  void init(int _n) {
    n = _n;
    for (int i = 0; i < n; ++i)
      g[i].clear(), ecc[i] = dp[i][0] = dp[i][1] = 0;
  }
  void add_edge(int v, int u, LL w) { // 0-index
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
  }
  void dfs_length(int v, int p) {
    for (auto T: g[v]) {
      int u; LL w;
      tie(u, w) = T;
      if (u == p) continue;
      dfs_length(u, v);
      LL length_from_u = dp[u][0] + w;
      if (dp[v][0] < length_from_u)
        dp[v][1] = dp[v][0], dp[v][0] = length_from_u;
      else if (dp[v][1] < length_from_u)
        dp[v][1] = length_from_u;
    }
  }
  void dfs_ecc(int v, int p, LL pass_p) {
    ecc[v] = max(dp[v][0], pass_p);
    for (auto T: g[v]) {
      int u; LL w;
      tie(u, w) = T;
      if (u == p) continue;
      if (dp[u][0] + w == dp[v][0])
        dfs_ecc(u, v, max(pass_p, dp[v][1]) + w);
      else dfs_ecc(u, v, max(pass_p, dp[v][0]) + w);
    }
  }
  LL diameter() {
    assert(~n);
    dfs_length(0, 0);
    dfs_ecc(0, 0, 0);
    return *max_element(ecc, ecc + n);
  }
} solver;
