const int MAXN = 1000;
template <class TC>
struct KM_matching { // if there's no edge, the weight is 0
// complexity: O(n^3), support for negetive edge
  int n, matchy[MAXN];
  bool visx[MAXN], visy[MAXN];
  TC adj[MAXN][MAXN], coverx[MAXN], covery[MAXN], slack[MAXN];
  KM_matching(int _n) : n(_n) {
    memset(matchy, -1, sizeof(matchy));
    memset(covery, 0, sizeof(covery));
    memset(adj, 0, sizeof(adj));
  }
  void add_edge(int x, int y, TC w) { adj[x][y] = w; }
  bool aug(int u) {
    visx[u] = true;
    for (int v = 0; v < n; ++v)
      if (not visy[v]) {
        TC t = coverx[u] + covery[v] - adj[u][v];
        if (t == 0) { // The edge is in Equality subgraph
          visy[v] = true;
          if (matchy[v] == -1 or aug(matchy[v])) 
            return matchy[v] = u, true;
        }
        else if (slack[v] > t) slack[v] = t;
      }
    return false;
  }
  TC solve() {
    for (int u = 0; u < n; ++u)
      coverx[u] = *max_element(adj[u], adj[u] + n);
    for (int u = 0; u < n; ++u) {
      fill(slack, slack + n, INT_MAX);
      while (memset(visx, 0, sizeof(visx)), 
             memset(visy, 0, sizeof(visy)), 
             not aug(u)) {
        TC d = INT_MAX;
        for (int v = 0; v < n; ++v) 
          if (not visy[v]) d = min(d, slack[v]);
        for (int v = 0; v < n; ++v) {
          if (visx[v]) coverx[v] -= d;
          if (visy[v]) covery[v] += d;
        }
      }
    }
    return accumulate(coverx, coverx + n, (TC)0) + 
           accumulate(covery, covery + n, (TC)0);
  }
};
