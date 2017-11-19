#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL,LL> PLL;
vector<PLL> g[1000];//node, time
LL dp[1000][1000] = {0};
LL G[1000], d[1000];
int main() {
  LL u, v, t, N, M, ans = 0; scanf("%lld%lld", &N, &M);
  for (LL i = 0; i < N; ++i) {
    scanf("%lld%lld", G + i, d + i);
  }
  for (LL i = 0; i < M; ++i) {
    scanf("%lld%lld%lld", &u, &v, &t);
    --u, --v;
    g[u].push_back({v, t});
    g[v].push_back({u, t});
  }
  for (int i = 0; i < N; ++i) fill(dp[i], dp[i] + 1000, -1);
  dp[0][0] = G[0];
  for (LL t = 1; t < 1000; ++t) {
    for (LL i = 0; i < N; ++i) {
      for (PLL P: g[i]) {
        v = P.first, u = P.second;
        if (t - u >= 0 and dp[t - u][v] != -1)
          dp[t][i] = max(dp[t][i], dp[t - u][v] + max(0ll, G[i] - d[i] * t));
      }
      if (dp[t][i] != -1) ans = max(ans, dp[t][i]);
    }
  }
  printf("%lld\n", ans);
}
