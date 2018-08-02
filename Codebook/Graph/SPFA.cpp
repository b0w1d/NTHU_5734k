struct SPFA {
  const LL INF = 1ll<<62;
  vector<vector<pair<int, LL>>> g;
  vector<int> p;
  vector<LL> d;
  int n;
  void init(int _n) {
    n = _n;
    g.assign(n, vector<pair<int, LL>>(0));
    d.assign(n, INF);
    p.assign(n, -1);
  }
  void add_edge(int u, int v, LL w) {
    g[u].push_back({v, w});
  }
  LL shortest_path(int s, int t) {
    for (int i = 0; i < n; ++i)
      sort(g[i].begin(), g[i].end(), [](pair<int, LL> A, pair<int, LL> B) {
        return A.second < B.second;
      });
    vector<bool> inq(n, false);
    vector<int> inq_t(n, 0);
    queue<int> q;
    q.push(s);
    d[s] = 0, inq_t[s] = 1;
    int u, v;
    LL w;
    while (q.size()) {
      inq[v = q.front()] = false; q.pop();
      for (auto P: g[v]) {
        tie(u, w) = P;
        if (d[u] > d[v] + w) {
          d[u] = d[v] + w, p[u] = v;
          if (not inq[u]) {
            q.push(u), inq[u] = true, ++inq_t[u];
            if (inq_t[u] > n) return -INF;
          }
        }
      }
    }
    return d[t];
  }
}solver;
