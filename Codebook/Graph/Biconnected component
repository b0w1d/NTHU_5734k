#include <bits/stdc++.h>

using namespace std;

class biconnected_component {
  public:
  vector< vector<int> > g;
  vector< vector<int> > comp;
  vector<int> pre, depth;
  int n;
  int iter;

  biconnected_component(int _n) : n(_n) {
    depth = vector<int>(n, -1);
    pre.resize(n);
    g.resize(n);
    iter = 0;
  }

  void add(int u, int v) {
    assert(0 <= u && u < n && 0 <= v && v < n);
    g[u].push_back(v);
    g[v].push_back(u);
  }

  int dfs(int v, int pa, int d) {
    pre[iter++] = v;
    depth[v] = d;
    for (int u : g[v]) {
      if (u == pa) continue;
      if (depth[u] == -1) {
        int child = dfs(u, v, depth[v] + 1);
        if (child >= depth[v]) {
          comp.push_back(vector<int>(1, v));
          while (v != pre[iter - 1]) {
            comp.back().push_back(pre[--iter]);
          }
        }
        d = min(d, child);  
      }
      else {
        d = min(d, depth[u]);
      }
    }
    return d;
  }

  vector< vector<int> > solve() {
    for (int i = 0; i < n; i++) {
      if (depth[i] == -1) {
        dfs(i, -1, 0);
      }
    }
    return comp;
  }

  vector<int> get_ap() {
    vector<int> res, count(n, 0);
    for (auto c : comp) {
      for (int v : c ) {
        count[v]++;
      }
    }
    for (int i = 0; i < n; i++) {
      if (count[i] > 1) {
        res.push_back(i);
      }
    }
    return res;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m, u, v;
  bool newline = false;
  while (cin >> n >> m) {
    if (n == 0 && m == 0) break;
    if (newline) cout << "\n";
    newline = true;
    biconnected_component bcc(n);
    for (int i = 0; i < m; i++) {
      cin >> u >> v;
      bcc.add(u, v);
    }
    bcc.solve();
    vector<int> ans = bcc.get_ap();
    if (ans.size() == 0) {
      cout << "None.\n";
    }
    else {
      for (int i : ans) {
        cout << i << "\n";
      }
    }
  }
  return 0;
}
