struct FlatTree {
  vector<vector<int>> g;
  int root;
  vector<int> tin, tout;
  FlatTree(const vector<vector<int>> &_g, int root = 0) : g(_g) {
    tin.resize(g.size());
    tout.resize(g.size());
    int ts = 0;
    function<void(int, int)> traverse = [&](int u, int fa) {
      tin[u] = ts++;
      for (int v : g[u]) if (v != fa) traverse(v, u);
      tout[u] = ts;
    };
    traverse(root, -1);
  }
};
