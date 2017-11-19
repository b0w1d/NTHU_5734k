#ifdef __APPLE__
#include "bits:stdc++.h"
#else
#include <bits/stdc++.h>
#endif

using namespace std;
typedef long long LL;
typedef pair<LL, LL> PLL;
auto scan = []{ static LL a; scanf("%lld", &a); return a;};
#define MAXN 200000
LL a[MAXN], b[MAXN], u[MAXN], d[MAXN], ans[MAXN];

bool in(LL a, LL u, LL d) {
  return a <= u && d <= a;
}
int main() {
  LL n = scan();
  for (LL i = 0; i < n ; ++i) {
    a[i] = scan();
    b[i] = scan() + a[i];
  }
  u[0] = b[0], d[0] = a[0];
  for (LL i = 1; i < n; ++i ) {
    u[i] = min(u[i - 1] + 1, b[i]);
    d[i] = max(d[i - 1] - 1, a[i]);
    if(u[i] < d[i]) return 0 * puts("-1");
  }
  ans[n - 1] = u[n - 1];
  for (LL i = n - 2; i >= 0; --i) {
    if (in(ans[i+1] + 1, u[i],d[i])) ans[i] = ans[i+1] + 1;
    else if (in(ans[i+1], u[i],d[i])) ans[i] = ans[i+1];
    else if (in(ans[i+1] - 1, u[i],d[i])) ans[i] = ans[i+1] - 1;
    else assert(0);
  }
  LL AAA = 0;
  for (LL i = 0; i < n ; ++i ) AAA += ans[i] - a[i];
  printf("%lld\n",AAA);
  for (LL i = 0; i < n ; ++i ) printf("%lld%c",ans[i]," \n"[i==n-1]);
}
