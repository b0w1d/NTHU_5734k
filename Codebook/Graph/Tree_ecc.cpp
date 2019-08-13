struct Tree_ecc {
  vector<vector<pair<int, long long>>> g; 
  vector<vector<long long>> dp;
  vector<long long> ecc;
  int n = -1;
  void dfs_length(int u, int p) {
    for (auto [v, w] : g[u]) if (v != p) {
      dfs_length(v, u);
      long long length_from_v = dp[v][0] + w;
      if (dp[u][0] < length_from_v)
        swap(dp[u][1], dp[u][0]), dp[u][0] = length_from_v;
      else dp[u][1] = max(dp[u][1], length_from_v);
    }
  }
  void dfs_ecc(int u, int p, long long pass_p) {
    ecc[u] = max(dp[u][0], pass_p);
    for (auto [v, w] : g[u]) if (v != p) {
      if (dp[v][0] + w == dp[u][0]) dfs_ecc(v, u, max(pass_p, dp[u][1]) + w);
      else dfs_ecc(v, u, max(pass_p, dp[u][0]) + w);
    }
  }
public:
  Tree_ecc(vector<vector<int>> _g) {
    int n = _g.size();
    g.resize(n);
    ecc.assign(n, 0);
    dp.assign(n, vector<long long>{0, -(1ll<<60)});
    for (int i = 0; i < n; ++i) for (int v : _g[i]) g[i].emplace_back(v, 1);
    dfs_length(0, 0), dfs_ecc(0, 0, 0);
  }
  Tree_ecc(vector<vector<pair<int, long long>>> g) : g(g) {
    int n = g.size();
    ecc.resize(n, 0);
    dp.assign(n, vector<long long>{0, -(1ll<<60)});
  }
  const vector<long long>& get_ecc() { return ecc; }
};
