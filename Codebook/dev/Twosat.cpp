class Twosat {
 private:
  void dfs_topo(int u, vector<int> &stk, vector<int> &vis) {
    for (int v : g[u]) {
      if (vis[v]) continue;
      vis[v] = 1;
      dfs_topo(v, stk, vis);
    }
    stk.emplace_back(u);
  }
  void dfs_ksrj(int u, vector<int> &scc, int scc_id) {
    for (int v : rg[u]) {
      if (scc[v]) continue;
      scc[v] = scc_id;
      dfs_ksrj(v, scc, scc_id);
    }
  }
 public:
  int n;
  vector<vector<int>> g, rg;
  Twosat(int _n) : n(_n), g(_n * 2), rg(_n * 2) {}
  int negate(int u) { return u < n ? n + u : u - n; }
  void if_then(int a, int b) {
    g[a].push_back(b);
    rg[b].push_back(a);
  }
  void either(int a, int b) {
    if_then(a, negate(b));
    if_then(b, negate(a));
    if_then(negate(a), b);
    if_then(negate(b), a);
  }
  void either_or_none(int a, int b) {
    if_then(a, negate(b));
    if_then(b, negate(a));
  }
  void either_or_both(int a, int b) {
    if_then(negate(a), b);
    if_then(negate(b), a);
  }
  void assure(int a) { if_then(negate(a), a); }
  vector<bool> solve() {
    int scc_cnt = 0;
    vector<int> stk;
    vector<int> scc(n * 2);
    vector<int> vis(n * 2);
    for (int i = 0; i < n * 2; ++i) {
      if (vis[i]) continue;
      vis[i] = 1;
      dfs_topo(i, stk, vis);
    }
    for (int i = n * 2 - 1; ~i; --i) {
      if (scc[stk[i]]) continue;
      scc[stk[i]] = ++scc_cnt;
      dfs_ksrj(stk[i], scc, scc_cnt);
    }
    for (int i = 0; i < n; ++i) {
      if (scc[i] == scc[n + i]) {
        return {}; // no solution
      }
    }
    vector<int> sat(scc_cnt + 1);
    for (int i = n * 2 - 1; ~i; --i) {
      int u = stk[i];
      int v = negate(u);
      if (sat[scc[u]]) {
        sat[scc[v]] = 3 - sat[scc[u]];
      } else if (sat[scc[v]]) {
        sat[scc[u]] = 3 - sat[scc[v]];
      } else {
        sat[scc[u]] = 2;
        sat[scc[v]] = 1;
      }
    }
    vector<bool> sol(n);
    for (int i = 0; i < n; ++i) {
      sol[i] = sat[scc[i]] & 1;
    }
    return sol;
  }
};
