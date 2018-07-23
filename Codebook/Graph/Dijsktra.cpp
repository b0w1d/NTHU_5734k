struct Dijsktra {
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
    g[v].push_back({u, w}), g[u].push_back({v, w});
  }
  LL shortest_path(int s, int t) {
    priority_queue<pair<LL, int>, vector<pair<LL, int>>, greater<>> q;
    d[s] = 0;
    q.push({d[s], s});
    int u, v;
    LL w;
    while (q.size()) {
      tie(w, v) = q.top(); q.pop();
      if (w > d[v]) continue;
      for (auto P: g[v]) {
        tie(u, w) = P;
        if (d[u] > d[v] + w)
          d[u] = d[v] + w, p[u] = v, q.push({d[u], u});
      }
    }
    return d[t];
  }
}solver;
