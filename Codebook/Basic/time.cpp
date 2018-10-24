#include <bits/stdc++.h>

using namespace std;

int main() {
  clock_t t;
  t = clock();
  // code here
  t = clock() - t;
  cout << 1.0 * t / CLOCKS_PER_SEC << "\n";
  
  // execute time for entire program
  cout << 1.0 * clock() / CLOCKS_PER_SEC << "\n";
}
