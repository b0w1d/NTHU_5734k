#include <bits/stdc++.h>
using namespace std;

int N;

signed main() {
  ios::sync_with_stdio(false);
  cin >> N;
  set<string> bag;
  for (int t = 0; t < N; ++t) {
    string S;
    cin >> S;
    vector<char> vec;
    for (int i = 0; i < S.size(); ++i) {
      if (S[i] == 'o') {
        int oc = 0, uc = 0;
        int j = i;
        while (j < S.size() && (S[j] == 'o' || S[j] == 'u')) {
          oc += S[j] == 'o';
          uc += S[j] == 'u';
          ++j;
        }
        for (int k = 0; k < uc; ++k) vec.emplace_back('u');
        for (int k = 0; k < oc; ++k) vec.emplace_back('o');
        i = j - 1;
      } else {
        vec.emplace_back(S[i]);
      }
    }
    for (int i = 1; i < vec.size(); ) {
      if (vec[i - 1] == 'o' && vec[i] == 'o') {
        vec.erase(vec.begin() + i - 1);
        vec.erase(vec.begin() + i - 1);
        vec.emplace(vec.begin() + i - 1, 'u');
      } else if (vec[i - 1] == 'k' && vec[i] == 'h') {
        vec.erase(vec.begin() + i - 1);
        --i;
      } else ++i;
    }
    S = "";
    for (int i = 0; i < vec.size(); ++i) {
      S += vec[i];
    }
    bag.emplace(S);
  }
  cout << bag.size() << endl;
  return 0;
}
