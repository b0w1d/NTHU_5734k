#include <bits/stdc++.h>

using namespace std;

class two_SAT {
  public:
  vector< vector<int> > g, rg;
  vector<int> visit, was;
  vector<int> id;
  vector<int> res;
  int n, iter;

  two_SAT(int _n) : n(_n) {
    g.resize(n * 2);
    rg.resize(n * 2);
    was = vector<int>(n * 2, 0);
    id = vector<int>(n * 2, -1);
    res.resize(n);
    iter = 0;
  }

  void add_edge(int from, int to) { // add (a -> b)
    assert(from >= 0 && from < 2 * n && to >= 0 && to < 2 * n);
    g[from].emplace_back(to);
    rg[to].emplace_back(from);
  }

  void add_or(int a, int b) { // add (a V b)
    int nota = (a < n) ? a + n : a - n;
    int notb = (b < n) ? b + n : b - n;
    add_edge(nota, b);
    add_edge(notb, a);
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

  int scc() {
    for (int i = 0; i < 2 * n; i++) {
      if (!was[i]) dfs(i);
    }
    for (int i = 2 * n - 1; i >= 0; i--) {
      if (id[ visit[i] ] == -1) {
        rdfs(visit[i]);
        iter++;
      }
    }
    return iter;
  }

  bool solve() {
    scc();
    for (int i = 0; i < n; i++) {
      if (id[i] == id[i + n]) return false;
      res[i] = (id[i] < id[i + n]);
    }
    return true;
  }

};

/*
  usage:
    index 0 ~ n - 1 : True
    index n ~ 2n - 1 : False
    add_or(a, b) : add SAT (a or b)
    add_edge(a, b) : add SAT (a -> b)
    if you want to set x = True, you can add (not X -> X)
    solve() return True if it exist at least one solution
    res[i] store one solution
      false -> choose a
      true -> choose a + n
*/
