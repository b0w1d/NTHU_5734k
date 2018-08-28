#include <bits/stdc++.h>

using namespace std;

class SCC {
  public:
  vector< vector<int> > g, rg;
  vector<int> visit, was;
  vector<int> id;
  int n, iter;

  SCC(int _n) : n(_n) {
    g.resize(n);
    rg.resize(n);
    was = vector<int>(n, 0);
    id = vector<int>(n, -1);
    iter = 0;
  }

  void add(int from, int to) {
    assert(from >= 0 && from < n && to >= 0 && to < n);
    g[from].emplace_back(to);
    rg[to].emplace_back(from);
  }

  void dfs(int v) {
    was[v] = true;
    for (int u : g[v]) {
      if (!was[u]) dfs(u);
    }
    visit.emplace_back(v);
  }

  void rdfs(int v) {
    id[v] = iter;
    for (int u : rg[v]) {
      if (id[u] == -1) rdfs(u);
    }
  }

  int solve() {
    for (int i = 0; i < n; i++) {
      if (!was[i]) dfs(i);
    }
    for (int i = n - 1; i >= 0; i--) {
      if (id[ visit[i] ] == -1) {
        rdfs(visit[i]);
        iter++;
      }
    }
    return iter;
  }
};

/*
  Kosaraju's algorithm
  solve() return the number of scc
  node with same id[] belong the same scc
*/

int main() {
  int n, m;
  while (cin >> n >> m && n && m) {
    SCC scc(n);
    for (int i = 0; i < m; i++) {
      int u, v;
      cin >> u >> v;
      scc.add(u, v);
    }
    cout << scc.solve() << "\n";
  }
  return 0;
}
