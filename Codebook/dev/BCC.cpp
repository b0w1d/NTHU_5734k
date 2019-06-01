struct BCC {
  vector<vector<int> > g;
  vector<vector<int> > comp;
  vector<int> pre, depth;
  int n;
  biconnected_component(int _n) : n(_n) {
    depth = vector<int>(n, -1);
    g.resize(n);
  }
  void add(int u, int v) {
    assert(0 <= u && u < n && 0 <= v && v < n);
    g[u].push_back(v);
    g[v].push_back(u);
  }
  int dfs(int v, int pa, int d) {
    depth[v] = d;
    pre.push_back(v);
    for (int u : g[v]) {
      if (u == pa) continue;
      if (depth[u] == -1) {
        int child = dfs(u, v, depth[v] + 1);
        if (child >= depth[v]) {
          comp.push_back(vector<int>(1, v));
          while (pre.back() != v) {
            comp.back().push_back(pre.back());
            pre.pop_back();
          }
        }
        d = min(d, child);
      } else {
        d = min(d, depth[u]);
      }
    }
    return d;
  }
  vector<vector<int> > solve() {
    for (int i = 0; i < n; i++) {
      if (depth[i] == -1) {
        dfs(i, -1, 0);
      }
    }
    return comp;
  }
  vector<int> get_ap() {
    vector<int> res, count(n, 0);
    for (auto c : comp) {
      for (int v : c) {
        count[v]++;
      }
    }
    for (int i = 0; i < n; i++) {
      if (count[i] > 1) {
        res.push_back(i);
      }
    }
    return res;
  }
};
