class matching {
  public:
  vector< vector<int> > g;
  vector<int> pa, pb, was;
  int n, m, res, iter;

  matching(int _n, int _m) : n(_n), m(_m) {
    assert(0 <= n && 0 <= m);
    pa = vector<int>(n, -1);
    pb = vector<int>(m, -1);
    was = vector<int>(n, 0);
    g.resize(n);
    res = 0, iter = 0;
  }

  void add_edge(int from, int to) {
    assert(0 <= from && from < n && 0 <= to && to < m);
    g[from].push_back(to);
  }

  bool dfs(int v) {
    was[v] = iter;
    for (int u : g[v])
      if (pb[u] == -1)
        return pa[v] = u, pb[u] = v, true;
    for (int u : g[v])
      if (was[pb[u]] != iter && dfs(pb[u]))
        return pa[v] = u, pb[u] = v, true;
    return false;
  }

  int solve() {
    while (true) {
      iter++;
      int add = 0;
      for (int i = 0; i < n; i++)
        if (pa[i] == -1 && dfs(i))
          add++;
      if (add == 0) break;
      res += add;
    }
    return res;
  }

  int run_one(int v) {
    if (pa[v] != -1) return 0;
    iter++;
    return (int) dfs(v);
  }
  pair<vector<bool>, vector<bool>> vertex_cover() {
    solve();
    vector<bool> a_cover(n, true), b_cover(m, false);
    function<void(int)> dfs_aug = [&](int v) {
      a_cover[v] = false;
      for (int u: g[v])
        if (not b_cover[u])
          b_cover[u] = true, dfs_aug(pb[u]);
    };
    for (int v = 0; v < n; ++v)
      if (a_cover[v] and pa[v] == -1)
        dfs_aug(v);
    return {a_cover, b_cover};
  }
};
