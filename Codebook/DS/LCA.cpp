const int LOG = 20, N = 200000;
vector<int> g[N];
int par[N][LOG], tin[N], tout[N];
bool anc(int u, int p) {
  return tin[p] <= tin[u] and tout[u] <= tout[p];
}
void dfs(int v, int p) { // root's parent is root
  par[v][0] = p;
  for (int j = 1; j < LOG; ++j)
    par[v][j] = par[par[v][j - 1]][j - 1];
  static int timer = 0;
  tin[v] = timer++;
  for (int u: g[v]) {
    if (u == p) continue;
    dfs(u, v);
  }
  tout[v] = timer++;
}
int lca(int x, int y) {
  if (anc(x, y)) return y;
  for (int j = LOG - 1; j >= 0; --j)
    if (not anc(x, par[y][j])) y = par[y][j];
  return par[y][0];
}