struct Dsu {
  struct node_struct {
    int par, size;
    node_struct(int p, int s) : par(p), size(s) {}
    void merge(node_struct &b) {
      b.par = par;
      size += b.size;
    }
  };
  vector<node_struct> nodes;
  stack<tuple<int, int, node_struct, node_struct>> stk;
  Dsu(int n) {
    nodes.reserve(n);
    for (int i = 0; i < n; ++i) nodes.emplace_back(i, 1);
  }
  int anc(int x) {
    while (x != nodes[x].par) x = nodes[x].par;
    return x;
  }
  bool unite(int x, int y) {
    int a = anc(x);
    int b = anc(y);
    stk.emplace(a, b, nodes[a], nodes[b]);
    if (a == b) return false;
    if (nodes[a].size < nodes[b].size) swap(a, b);
    nodes[a].merge(nodes[b]);
    return true;
  }
  void revert(int version = -1) {  // 0 index
    if (version == -1) version = stk.size() - 1;
    for (; stk.size() != version; stk.pop()) {
      nodes[get<0>(stk.top())] = get<2>(stk.top());
      nodes[get<1>(stk.top())] = get<3>(stk.top());
    }
  }
};
