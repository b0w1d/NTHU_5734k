struct MaxClique {
  int n;
  vector<vector<int>> es;
  vector<int> dp;
  vector<vector<int>> s;
  vector<int> sol;
  int ans;

  MaxClique(int _n)
      : n(_n),
        ans(0),
        es(_n, vector<int>(_n / 32 + 2)),
        dp(_n),
        s(_n + 1, vector<int>(_n / 32 + 2)) {}

  void add_edge(int u, int v) {
    if (u > v) swap(u, v);
    if (u == v) return;
    es[u][v / 32] |= (1 << (v % 32));
  }

  bool dfs(int v, int k) {
    int c = 0;
    int d = 0;
    for (int i = 0; i < (n + 31) / 32; ++i) {
      s[k][i] = es[v][i];
      if (k != 1) s[k][i] &= s[k - 1][i];
      c += __builtin_popcount(s[k][i]);
    }
    if (c == 0) {
      if (k > ans) {
        ans = k;
        sol.clear();
        sol.push_back(v);
        return 1;
      }
      return 0;
    }
    for (int i = 0; i < (n + 31) / 32; ++i) {
      for (int a = s[k][i]; a; ++d) {
        if (k + (c - d) <= ans) return 0;
        int lb = a & (-a), lg = 0;
        a ^= lb;
        while (lb != 1) {
          lb = (unsigned int)(lb) >> 1;
          lg++;
        }
        int u = i * 32 + lg;
        if (k + dp[u] <= ans) return 0;
        if (dfs(u, k + 1)) {
          sol.push_back(v);
          return 1;
        }
      }
    }
    return 0;
  }

  int solve() {
    for (int i = n - 1; ~i; --i) {
      dfs(i, 1);
      dp[i] = ans;
    }
    return ans;
  }
};
