
vector<int> UndirectedEulersPath(vector<multiset<int>> g) {
  int oddc = 0;
  int ec = 0;
  int ed = 0;
  for (int u = 0; u < g.size(); ++u) {
    ec += g[u].size();
    if (g[u].size() & 1) {
      ++oddc;
      ed = u;
    }
  }
  vector<int> path;
  if (!(oddc == 0 || oddc == 2)) return path;
  function<void(int)> dfs = [&](int u) {
    while (g[u].size()) {
      int v = *g[u].begin();
      g[u].erase(g[u].begin());
      g[v].erase(g[v].find(u));
      dfs(v);
    }
    path.push_back(u);
  };
  dfs(ed);
  if (path.size() != ec / 2 + 1) return {};
  return path;
}