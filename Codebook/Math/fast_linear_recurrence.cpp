#include <bits/stdc++.h>
using namespace std;

vector<int> fast_linear_recurrence(const vector<int> &t, long long p, int mod) { // O(lg(p) * t.size()**2)
  assert(p > t.size());

  auto advance = [&](const vector<int> &u) {
    vector<int> v(t.size());
    v[0] = 1LL * u.back() * t[0] % mod;
    for (int i = 1; i < t.size(); ++i) v[i] = (u[i - 1] + 1LL * u.back() * t[i]) % mod;
    return v;
  };

  vector<vector<int>> kk(t.size(), vector<int>(t.size())); // kk[i] = lambda(t ** (t.size + i))
  for (int i = 0; i < t.size(); ++i) kk[i] = i ? advance(kk[i - 1]) : t;

  auto square = [&](const vector<int> &u) {
    vector<int> v(2 * t.size());
    for (int j = 0; j < u.size(); ++j)
      for (int k = 0; k < u.size(); ++k)
        v[j + k] = (v[j + k] + 1LL * u[j] * u[k]) % mod;
    for (int j = u.size(); j < v.size(); ++j)
      for (int k = 0; k < u.size(); ++k)
        v[k] = (v[k] + 1LL * v[j] * kk[j - u.size()][k]) % mod;
    v.resize(u.size());
    return v;
  };

  vector<int> m(t.size());
  m[1] = 1; // T[0] = {0, 1, 0, 0, ...}
  for (int i = 62 - __builtin_clzll(p); ~i; --i) {
    m = square(m);
    if (p >> i & 1) m = advance(m);
  }
  
  return m;
}

signed main() { // Project Euler 258, 3833 ms on CF
  int mod = 20092010;
  vector<int> t(2000);
  t[0] = t[1] = 1; // f[i] = f[i - 2000] + f[i - 1999]
  auto m = fast_linear_recurrence(t, (long long) 1e18, mod);

  vector<int> v(2000, 1); // f[i] = 1 for i < 2000
  int res = 0;
  for (int i = 0; i < m.size(); ++i)
    res = (res + 1LL * v[i] * m[i]) % mod;
  if (res < 0) res += mod;
  cout << res << endl;

  return 0;
}
