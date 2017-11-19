#include <bits/stdc++.h>
using namespace std;
struct edge {
  int v, l, r;
};
vector<edge> g[1000];
vector<int> nums;
int s, d, vis[1000] = {0};
bool bfs(int l, int r) {
  static int V = 0; ++V;
  queue<int> q;
  q.push(s), vis[s] = V;
  while (!q.empty()) {
    int v = q.front(); q.pop();
    for (edge E : g[v]) {
      int u = E.v, L = E.l, R = E.r;
      if (vis[u] != V and L <= l and r <= R) {
        vis[u] = V, q.push(u);
        if (u == d) return true;
      }
    }
  }
  return vis[d] == V;
}
int main() {
  map<int, int> toid;
  int n, m, k, ans = 0; scanf("%d%d%d%d%d", &n, &m, &k, &s, &d);
  ++k, --s, --d;
  nums.push_back(1), nums.push_back(k + 1);
  for (int u, v, l, r, i = 0; i < m; ++i) {
    scanf("%d%d%d%d", &u, &v, &l, &r);
    --v, --u, ++r;
    g[u].push_back({v, l, r});
    nums.push_back(l);
    nums.push_back(r);
  }
  sort(nums.begin(), nums.end());
  nums.resize(unique(nums.begin(), nums.end()) - nums.begin());
  for (int i = 0; i < nums.size() - 1; ++i) {
    if (bfs(nums[i], nums[i + 1])) ans += nums[i + 1] - nums[i];
  }
  printf("%d\n", ans);
}
