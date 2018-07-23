struct SPFA {
  vector<vector<pair<int, LL>>> g;
  vector<int> p;
  vector<LL> d;
  int n;
  void init(int _n) {
    n = _n;
    g.assign(n, vector<pair<int, LL>>(0));
    d.assign(n, 1ll << 62);
    p.assign(n, -1);
  }
  void add_edge(int u, int v, LL w) {
    g[v].push_back({u, w});
    g[u].push_back({v, w});
  }
  LL shortest_path(int s, int t) {
    for (int i = 0; i < n; ++i)
      sort(g[i].begin(), g[i].end(), [](auto A, auto B) {
        return A.second < B.second;
      });
    vector<bool> inq(n, false);
    queue<int> q;
    q.push(s);
    d[s] = 0;
    int u, v;
    LL w;
    while (q.size()) {
      inq[v = q.front()] = false; q.pop();
      for (auto P: g[v]) {
        tie(u, w) = P;
        if (d[u] > d[v] + w) {
          d[u] = d[v] + w, p[u] = v;
          if (not inq[u])
            q.push(u), inq[u] = true;
        }
      }
    }
    return d[t];
  }
}solver;
