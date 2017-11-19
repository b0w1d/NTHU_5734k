#ifdef __APPLE__
#include "bits:stdc++.h"
#else
#include <bits/stdc++.h>
#endif

using namespace std;
typedef long long LL;
typedef pair<LL, LL> PLL;
auto scan = []{ static LL a; scanf("%lld", &a); return a;};
#define MAXN 500000
LL c[256] = {0};
char s[MAXN];
void printdq(deque<LL> &dq) {
  while(dq.size()) printf("%c", (char)dq.back()), dq.pop_back();
  dq.clear();
}
int main() {
  LL n = scan();
  scanf("%s",s);
  for (LL i = 0; i < n; ++i) {
    ++c[s[i]];
  }
  vector<LL> left;
  for (LL i = 0; i < 256; ++i) {
    if(c[i] & 1) {
      left.push_back(i);
      --c[i];
    }
  }
  for (LL i = 1; i <= n; ++i) {
    if (n % i == 0) {
      if ((n / i) % 2 == 0) {
        if (left.size()) continue;
        printf("%lld\n",i);
        deque<LL> dq;
        LL now = 0;
        for (LL j = 0; j < i; ++j){
          for (LL k = 0; k < (n/i)/2; ++k){
            while(c[now] == 0) ++now;
            dq.push_back(now),dq.push_front(now);
            c[now]-=2;
          }
          printdq(dq);
          printf("%c"," \n"[j==i-1]);
        }
        return 0;
      }
      else {
        LL totake = i - left.size();
        if (totake < 0 || totake % 2 == 1) continue;
        printf("%lld\n",i);
        for (LL i = 0; i < 256; ++i ){
          while (totake && c[i]) --totake, --c[i], left.push_back(i);
        }
        deque<LL> dq;
        LL now = 0;
        for(LL j = 0; j < i; ++j){
          dq.push_front(left.back()),left.pop_back();
          for(LL k = 0; k < (n/i - 1)/2; ++k){
            while(c[now] == 0) ++now;
            dq.push_back(now),dq.push_front(now);
            c[now]-=2;
          }
          printdq(dq);
          printf("%c"," \n"[j==i-1]);
        }
        return 0;
      }
    }
  }
}
