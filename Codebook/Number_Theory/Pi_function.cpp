#include <bits/stdc++.h>
typedef long long LL;
using namespace std;

LL Pi(LL m);
const int UPBD = 1000001;
LL d[UPBD] = {0}, dp_phi[1000][1000];
vector<LL> primes;
void init() {
  memset(dp_phi, -1, sizeof(dp_phi));
  fill(d + 2, d + UPBD, 1);
  for (int p = 2; p * p <= UPBD; ++p) 
    if (d[p]) {
      for (int N = p * p; N <= UPBD; N += p) 
        d[N] = 0;
      primes.push_back(p);
    }
  for (int i = 1; i < UPBD; ++i) d[i] += d[i - 1];
}
LL P_2(LL m, LL n) {
  LL ans = 0;
  for (LL i = n; primes[i] * primes[i] <= m and i < primes.size(); ++i) 
    ans += Pi(m / primes[i]) - i;
  return ans;
}
LL phi(LL m, LL n) {
  if (m < 1000 and n < 1000 and dp_phi[m][n] != -1) return dp_phi[m][n];
  if (n == 0 or m == 0) return m;
  LL ans = phi(m, n - 1) - phi(m / primes[n - 1], n - 1);
  if (m < 1000 and n < 1000) dp_phi[m][n] = ans;
  return ans;
}
LL Pi(LL m) {
  if (m < UPBD) return d[m];
  LL y = cbrt(m) + 10, n = d[y];
  return phi(m, n) + n - 1 - P_2(m, n);
}
int main() {
  LL n; init();
  while (~scanf("%lld", &n)) printf("%lld\n", Pi(n));
}
