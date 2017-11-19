#ifdef __APPLE__
#include "bits:stdc++.h"
#else
#include <bits/stdc++.h>
#endif

using namespace std;
typedef long long LL;
typedef pair<LL, LL> PLL;
auto scan = []{ static LL a; scanf("%lld", &a); return a;};
struct edge {
  LL to, dir;
};
#define MAXN 400000
vector<edge> g[MAXN];

LL egans[MAXN];
bool vis[MAXN];
LL dfs1(LL s){
  vis[s] = 1;
  LL ans = 0;
  for (edge E: g[s]) {
    LL u = E.to, dir = E.dir;
    if (vis[u]) continue;
    if (E.dir == 0){
      ans += dfs1(E.to);
    }
    else {
      egans[abs(dir)] = dir/abs(dir);
      ans += dfs1(E.to);
    }
  }
  return ans + 1;
}
LL dfs2(LL s){
  vis[s] = 1;
  LL ans = 0;
  for (edge E: g[s]) {
    LL u = E.to, dir = E.dir;
    if (vis[u]) continue;
    if (E.dir == 0){
      ans += dfs2(E.to);
    }
    else {
      egans[abs(dir)] = -dir/abs(dir);
    }
  }
  return ans + 1;
}
int main() {
  LL t,from,to,n = scan(), m = scan(), s = scan(), ithedge = 1;
  for (LL i = 0; i < m; ++i) {
    t = scan(), from = scan(), to = scan();
    if (t == 1) {
      g[from].push_back({to,0});
    }
    else if(t == 2){
      g[to].push_back({from,ithedge});
      g[from].push_back({to,-ithedge});
      ++ithedge;
    }
  }
  auto toc = [](LL i){
    if (i <= 0) return '+';
    return '-';
  };
  fill(vis,vis+n+10,false);
  fill(egans,egans+n+10,0);
  printf("%lld\n",dfs1(s));
  for (LL i = 1; i < ithedge; ++i)
    printf("%c",toc(egans[i]));
  puts("");
  fill(vis,vis+n+10,false);
  fill(egans,egans+n+10,0);
  printf("%lld\n",dfs2(s));
  for (LL i = 1; i < ithedge; ++i)
    printf("%c",toc(egans[i]));
  puts("");
}
