struct LCT { /* expected O(m + n); CF: N=6e6, M=6e6 random graph < 700ms */
  struct Node {
    int fa, val, dpt;
    vector<int> ch;
    Node() : fa(-1), val(0), dpt(0) {}
  };
  vector<Node> nodes;

  LCT(int n) : nodes(n) {}

  void modify(int x, int v) {
    nodes[x].val = v;
    for (int i = 0; i < nodes[x].ch.size(); ++i) {
      nodes[nodes[x].ch[i]].val = v;
      modify(nodes[x].ch[i], v);
    }
  }
  void maintain(int x) {
    for (int i = 0; i < nodes[x].ch.size(); ++i) {
      nodes[nodes[x].ch[i]].dpt = nodes[x].dpt + 1;
      maintain(nodes[x].ch[i]);
    }
  }
  int query(int x) { return nodes[x].val; }
  void link(int x, int y) {
    nodes[x].fa = y;
    nodes[x].dpt = nodes[y].dpt + 1;
    maintain(x);
    nodes[y].ch.emplace_back(x);
  }
  void cut(int x) {
    if (nodes[x].fa == -1) return;
    Node &s = nodes[nodes[x].fa];
    nodes[x].dpt = 0;
    maintain(x);
    for (int i = 0; i < s.ch.size(); ++i) {
      if (s.ch[i] == x) {
        for (int j = i; j < s.ch.size() - 1; ++j) s.ch[j] = s.ch[j + 1];
        s.ch.pop_back();
        break;
      }
    }
    nodes[x].fa = -1;
  }
  bool lca(int x, int y) {
    if (x == y) return true;
    for (int i = 0; i < nodes[x].ch.size(); ++i)
      if (lca(nodes[x].ch[i], y)) return true;
    return false;
  }
};

template<typename max_type = int, typename weight_type = int, max_type inf = 0x3f3f3f3f>
vector<max_type> raffica(const vector<vector<pair<weight_type, int>>> &g, int src) {
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
