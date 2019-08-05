struct CentroidDecomp {
  vector<vector<int>> g;
  vector<int> p, M, sz; 
  vector<bool> vis;
  int n;

  CentroidDecomp(vector<vector<int>> g) : g(g), n(g.size()) {
    p.resize(n);
    vis.assign(n, false);
    sz.resize(n);
    M.resize(n);
  }

  int divideAndConquer(int x) {

    vector<int> q = {x};
    p[x] = x;

    for (int i = 0; i < q.size(); ++i) {
      int u = q[i];
      sz[u] = 1;
      M[u] = 0;
      for (auto v : g[u]) if (not vis[v] and v != p[u]) {
        q.push_back(v), p[v] = u;
      }
    }

    reverse(begin(q), end(q));
    for (int u : q) if (p[u] != u) {
      sz[p[u]] += sz[u];
      M[p[u]] = max(sz[u], M[p[u]]);
    }

    for (int u : q) M[u] = max(M[u], int(q.size()) - sz[u]);

    int cent = *min_element(begin(q), end(q), 
                            [&](int x, int y) { return M[x] < M[y]; });

    vis[cent] = true;
    for (int u : g[cent]) if (not vis[u]) divideAndConquer(u);
    return cent;
  }
};
