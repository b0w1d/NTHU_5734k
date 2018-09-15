struct LCT {
  struct Node {
    int fa, val, dpt;
    set<int> ch;
    Node() : fa(-1), val(0), dpt(0) {}
  };
  vector<Node> nodes;

  LCT(int n) : nodes(n) {}

  void modify(int x, int v) {
    nodes[x].val = v;
    for (int y : nodes[x].ch) {
      nodes[y].val = v;
      modify(y, v);
    }
  }
  void maintain(int x) {
    for (int y : nodes[x].ch) {
      nodes[y].dpt = nodes[x].dpt + 1;
      maintain(y);
    }
  }
  int query(int x) { return nodes[x].val; }
  void link(int x, int y) {
    nodes[x].fa = y;
    nodes[x].dpt = nodes[y].dpt + 1;
    maintain(x);
    nodes[y].ch.emplace(x);
  }
  void cut(int x) {
    if (nodes[x].fa == -1) return;
    Node &s = nodes[nodes[x].fa];
    nodes[x].dpt = 0;
    maintain(x);
    s.ch.erase(x);
    nodes[x].fa = -1;
  }
  bool lca(int x, int y) {
    if (x == y) return true;
    for (int z : nodes[x].ch)
      if (lca(z, y)) return true;
    return false;
  }
};

template<typename max_type = int, typename weight_type = int, max_type inf = 0x3f3f3f3f>
vector<max_type> SPFA(const vector<vector<pair<weight_type, int>>> &g, int src) {
  LCT tree(g.size());
  queue<int> que;
  vector<max_type> d(g.size(), inf);
  d[src] = 0;
  que.emplace(src);
  tree.modify(src, 1);
  while (que.size()) {
    int x = que.front();
    que.pop();
    if (!tree.query(x)) continue;
    for (int i = 0; i < g[x].size(); ++i)  {
      int w, y;
      tie(w, y) = g[x][i];
      if (d[x] + w < d[y]) {
        if (tree.lca(y, x)) return {};
        d[y] = d[x] + w;
        que.emplace(y);
        tree.modify(y, 0);
        tree.nodes[y].val = 1;
        tree.cut(y);
        tree.link(y, x);
      }
    }
  }
  return d;
}
