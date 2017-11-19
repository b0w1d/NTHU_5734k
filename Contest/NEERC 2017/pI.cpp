#include <bits/stdc++.h>
using namespace std;

const int MAXN = int(3e5);

int N, K;
int V[MAXN];

bool ok(int x) {
  set<int> dp;
  dp.emplace(0);
  int ptr = 0;
  for (int i = K; i <= N; ++i) {
    while (V[i - 1] - V[ptr] > x) ++ptr;
    auto it = dp.lower_bound(ptr);
    if (it == dp.end() || i - *it < K) continue;
    dp.emplace(i);
  }
  return dp.count(N);
}

signed main() {
  ios::sync_with_stdio(false);
  cin >> N >> K;
  for (int i = 0; i < N; ++i) {
    cin >> V[i];
  }
  sort(V, V + N);
  int lb = -1, ub = 1 << 30;
  while (ub - lb > 1) {
    int mb = lb + ub >> 1;
    (ok(mb) ? ub : lb) = mb;
  }
  cout << ub << endl;
  return 0;
}

