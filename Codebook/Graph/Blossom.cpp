#define MAXN 505
struct Blossom {
  vector<int> g[MAXN];
  int pa[MAXN] = {0}, match[MAXN] = {0}, st[MAXN] = {0}, S[MAXN] = {0}, v[MAXN] = {0};
  int t, n;
  Blossom(int _n) : n(_n) {}
  void add_edge(int v, int u) { // 1-index
    g[u].push_back(v), g[v].push_back(u);
  }
  inline int lca(int x, int y) {
    ++t;
    while (v[x] != t) {
      v[x] = t;
      x = st[pa[match[x]]];
      swap(x, y);
      if (x == 0) swap(x, y);
    }
    return x;
  }
  inline void flower(int x, int y, int l, queue<int> &q) {
    while (st[x] != l) {
      pa[x] = y;
      if (S[y = match[x]] == 1) q.push(y), S[y] = 0;
      st[x] = st[y] = l, x = pa[y];
    }
  }
  inline bool bfs(int x) {
    for (int i = 1; i <= n; ++i) st[i] = i;
    memset(S + 1, -1, sizeof(int) * n);
    queue<int> q;
    q.push(x), S[x] = 0;
    while (q.size()) {
      x = q.front(), q.pop();
      for (size_t i = 0; i < g[x].size(); ++i) {
        int y = g[x][i];
        if (S[y] == -1) {
          pa[y] = x, S[y] = 1;
          if (not match[y]) {
            for (int lst; x; y = lst, x = pa[y])
              lst = match[x], match[x] = y, match[y] = x;
            return 1;
          }
          q.push(match[y]), S[match[y]] = 0;
        } else if (not S[y] and st[y] != st[x]) {
          int l = lca(y, x);
          flower(y, x, l, q), flower(x, y, l, q);
        }
      }
    }
    return 0;
  }
  inline int blossom() {
    int ans = 0;
    for (int i = 1; i <= n; ++i)
      if (not match[i] and bfs(i)) ++ans;
    return ans;
  }
};
