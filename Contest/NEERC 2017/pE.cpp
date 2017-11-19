#include <bits/stdc++.h>
using namespace std;

int N;
string gol;

signed main() {
  ios::sync_with_stdio(false);
  int ans = (1 << 26) - 1;
  cin >> N;
  cin >> gol;
  int called = 0;
  for (int i = 0; i < N; ++i) {
    if (gol[i] == '*') continue;
    called |= 1 << gol[i] - 'a';
    if (~ans >> gol[i] - 'a' & 1) continue;
    ans ^= 1 << gol[i] - 'a';
  }
  int M;
  cin >> M;
  for (int i = 0; i < M; ++i) {
    string S;
    cin >> S;
    int appear = 0;
    for (int j = 0; j < S.size(); ++j) {
      if (gol[j] != '*' && S[j] != gol[j]) {
        appear = (1 << 26) - 1;
      }
      if (called >> S[j] - 'a' & 1) {
        if (gol[j] == '*') {
          appear = (1 << 26) - 1;
        }
      }
      appear |= 1 << S[j] - 'a';
    }
    ans &= appear;
  }
  cout << __builtin_popcount(ans) << endl;
  return 0;
}
