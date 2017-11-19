#include <bits/stdc++.h>
using namespace std;
int main() {
  int n; scanf("%d", &n);
  for (int i = 2; i < n; ++i) {
    if (n >= 2 * i - 1 and 
      (n % (2 * i - 1) == i or n % (2 * i - 1) == 0)) 
      printf("%d %d\n", i , i - 1);
    if (n >= 2 * i and n % i == 0) printf("%d %d\n", i, i);
  }
}
