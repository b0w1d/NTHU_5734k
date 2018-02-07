#include <iostream>
#include <algorithm>
#include <cmath>
typedef long long LL;

LL mul(LL x, LL y, LL mod) {
  LL ans = 0, m = x % mod, s = 0, sgn = (x > 0) xor (y > 0)? -1: 1;
  for (x = abs(x), y = abs(y); y; y >>= 1, (m *= 2) %= mod) 
    if (y&1) (s += m) %= mod;
  return s * sgn;
}
LL modpow(LL x, LL p, LL mod){
  LL s = 1, m = x;
  for (; p; m = mul(m, m, mod), p >>= 1) 
    if (p&1) s = mul(s, m, mod);
  return s;
}

bool witness(LL a, LL n, LL u, int t) {
  LL x = modpow(a, u, n), nx;
  for (int i = 0; i < t; ++i, x = nx){
    nx = mul(x, x, n);
    if (nx == 1 and x != 1 and x != n - 1) return 1;
  }
  return x != 1;
}
const LL wits[7] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
bool miller_rabin(LL n, int s = 7) {
  if (n < 2) return 0;
  if (!(n & 1)) return n == 2;
  LL u = n - 1, t = 0;
  // n == u << t
  while (!(u&1)) u >>= 1, ++t;
  while (s--) {
    LL a = wits[s] % n;
    if (a and witness(a, n, u, t)) return 0;
  }
  return 1;
}
/*
LL f(LL x, LL n) {
  return (mul(x, x, n) + 1) % n;
}
LL pollard_rho(LL n) {
  if (!(n&1)) return 2;
  while (true) {
    LL y = 2, x = rand()%(n-1)+1, res = 1;
    for(int sz=2; res==1; sz*=2) {
      for(int i=0; i<sz && res<=1; i++) {
        x = f(x, n);
        res = __gcd(abs(x-y), n);
      }
      y = x;
    }
    if (res!=0 && res!=n) return res;
  }
}
*/
const int M = 100000001;
LL divisor[M] = {0};
int main() {
  for (int p = 2; p < M; ++p) if (not divisor[p]) for (LL N = p; N < M; N += p) divisor[N] = p; 
  for (int p = 2; p < M; ++p) {
    if (miller_rabin(p) xor p == divisor[p]) printf("p: %d with divisorisor %lld\n", p, divisor[p]);
    if (p % 10000000 == 0) printf("test completed under %d\n", p);
  }
}
