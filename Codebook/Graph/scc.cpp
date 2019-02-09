class Kosaraju {

  vector<vector<int>> g, rg, compo;
  vector<int> order, DAGID;
  vector<bool> vis;
  int n, iter;

  void make_rg() {
    for (int u = 0; u < n; ++u) for (int v : g[u]) rg[v].push_back(u);
  }

  void dfs_all() {
    function<void(int)> dfs = [&](int u) {
      vis[u] = true;
      for (int v : g[u]) if (not vis[v]) dfs(v);
      order.emplace_back(u);
    };
    for (int i = 0; i < n; ++i) if (not vis[i]) dfs(i);
  }

  void rdfs_all() {
    function<void(int)> rdfs = [&](int u) {
      DAGID[u] = iter;
      for (int v : rg[u]) if (DAGID[v] == -1) rdfs(v);
      compo.back().push_back(u);
    };
    for (int u : order) if (DAGID[u] == -1) {
      compo.push_back(vector<int>(0));
      rdfs(u), ++iter;
    }
  }

public:

  // remember that the graph is directed
  Kosaraju(vector<vector<int>> &_g) : n(_g.size()), g(_g) {
    rg.resize(n);
    compo.clear();
    make_rg();
    vis.assign(n, false);
    DAGID.assign(n, -1);
    iter = 0;

    dfs_all();
    reverse(order.begin(), order.end());
    rdfs_all();
  }

  const vector<vector<int>>& get_components() { return compo; }

  const vector<vector<int>> get_condensed_DAG(bool simple = true) {
    vector<vector<int>> ret(iter);
    for (int i = 0; i < iter; ++i) {
      for (int u : compo[i]) for (int v : g[u]) if (DAGID[v] != i) {
        ret[i].push_back(DAGID[v]);
      }
      if (simple) {
        sort(ret[i].begin(), ret[i].end());
        ret[i].resize(unique(ret[i].begin(), ret[i].end()) - ret[i].begin());
      }
    }
    return ret;
  }
};

