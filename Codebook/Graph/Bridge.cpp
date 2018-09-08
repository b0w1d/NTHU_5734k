struct Bridge {
  vector<int> imo;
  set<pair<int, int>> bridges; // all bridges (u, v), u < v
  vector<set<int>> bcc; // bcc[i] has all vertices that belong to the i'th bcc
  vector<int> at_bcc; // node i belongs to at_bcc[i]
  int bcc_ctr;

  Bridge(const vector<vector<int>> &g) : bcc_ctr(0) {
    imo.resize(g.size());
    bcc.resize(g.size());
    at_bcc.resize(g.size());
    vector<int> vis(g.size());
    vector<int> dpt(g.size());
    function<void(int, int, int)> mark = [&](int u, int fa, int d) {
      vis[u] = 1;
      dpt[u] = d;
      for (int v : G[u]) {
        if (v == fa) continue;
        if (vis[v]) {
          if (dpt[v] > dpt[u]) {
            ++imo[v];
            --imo[u];
          }
        } else mark(v, u, d + 1);
      }
    };
    mark(0, -1, 0);
    vis.assign(g.size(), 0);
    function<int(int)> expand = [&](int u) {
      vis[u] = 1;
      int s = imo[u];
      for (int v : G[u]) {
        if (vis[v]) continue;
        int e = expand(v);
        if (e == 0) bridges.emplace(make_pair(min(u, v), max(u, v)));
        s += e;
      }
      return s;
    };
    expand(0);
    fill(at_bcc.begin(), at_bcc.end(), -1);
    for (int u = 0; u < N; ++u) {
      if (~at_bcc[u]) continue;
      queue<int> que;
      que.emplace(u);
      at_bcc[u] = bcc_ctr;
      bcc[bcc_ctr].emplace(u);
      while (que.size()) {
        int v = que.front();
        que.pop();
        for (int w : G[v]) {
          if (~at_bcc[w] || bridges.count(make_pair(min(v, w), max(v, w)))) continue;
          que.emplace(w);
          at_bcc[w] = bcc_ctr;
          bcc[bcc_ctr].emplace(w);
        }
      }
      ++bcc_ctr;
    }
  }
};
