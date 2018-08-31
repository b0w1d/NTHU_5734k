struct Oracle {
  int lgn;
  vector<vector<int>> g;
  vector<int> dep;
  vector<vector<int>> par;
  vector<int> dfn;

  Oracle(const vector<vector<int>> &_g) : g(_g), lgn(ceil(log2(_g.size()))) {
    dep.resize(g.size());
    par.assign(g.size(), vector<int>(lgn + 1, -1));
    dfn.resize(g.size());

    function<void(int, int)> dfs = [&](int u, int fa) {
      static int t = 0;
      dfn[u] = t++;
      if (~fa) dep[u] = dep[fa] + 1;
      par[u][0] = fa;
      for (int v : g[u]) if (v != fa) dfs(v, u);
    };
    dfs(0, -1);

    for (int i = 0; i < lgn; ++i)
      for (int u = 0; u < g.size(); ++u)
        par[u][i + 1] = ~par[u][i] ? par[par[u][i]][i] : -1;
  }

  int lca(int u, int v) const {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = lgn; dep[u] != dep[v]; --i) {
      if (dep[u] - dep[v] < 1 << i) continue;
      u = par[u][i];
    }
    if (u == v) return u;
    for (int i = lgn; par[u][0] != par[v][0]; --i) {
      if (par[u][i] == par[v][i]) continue;
      u = par[u][i];
      v = par[v][i];
    }
    return par[u][0];
  }
};

struct VirtualTree { // CF 613D
  vector<int> cp;
  vector<vector<int>> g;
  vector<int> nodes;
  map<int, int> mp;

  VirtualTree(const vector<int> &_cp, const Oracle &oracle) : cp(_cp) {
    sort(cp.begin(), cp.end(), [&](int u, int v) { return oracle.dfn[u] < oracle.dfn[v]; });
    nodes = cp;
    for (int i = 0; i < nodes.size(); ++i) mp[nodes[i]] = i;
    g.resize(nodes.size());

    if (!mp.count(0)) {
      mp[0] = nodes.size();
      nodes.emplace_back(0);
      g.emplace_back(vector<int>());
    }

    vector<int> stk;
    stk.emplace_back(0);

    for (int u : cp) {
      if (u == stk.back()) continue;
      int p = oracle.lca(u, stk.back());
      if (p == stk.back()) {
        stk.emplace_back(u);
      } else {
        while (stk.size() > 1 && oracle.dep[stk.end()[-2]] >= oracle.dep[p]) {
          g[mp[stk.back()]].emplace_back(mp[stk.end()[-2]]);
          g[mp[stk.end()[-2]]].emplace_back(mp[stk.back()]);
          stk.pop_back();
        }
        if (stk.back() != p) {
          if (!mp.count(p)) {
            mp[p] = nodes.size();
            nodes.emplace_back(p);
            g.emplace_back(vector<int>());
          }
          g[mp[p]].emplace_back(mp[stk.back()]);
          g[mp[stk.back()]].emplace_back(mp[p]);
          stk.pop_back();
          stk.emplace_back(p);
        }
        stk.emplace_back(u);
      }
    }
    for (int i = 0; i + 1 < stk.size(); ++i) {
      g[mp[stk[i]]].emplace_back(mp[stk[i + 1]]);
      g[mp[stk[i + 1]]].emplace_back(mp[stk[i]]);
    }
  }
};
