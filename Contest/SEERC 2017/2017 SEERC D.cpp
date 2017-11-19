#include <bits/stdc++.h>
using namespace std;
int d[2000][2000];
bool g[2000][2000];
char get() {
  char c = getchar();
  while (c != '#' and c != '.') c = getchar();
  return c == '.';
}
int N, K, dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
typedef pair<int, int> PII;
bool in(int x, int y){
  return x >= 0 and x < N and y >= 0 and y < N;
}
int main() {
  scanf("%d%d", &N, &K);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) 
      d[i][j] = -1, g[i][j] = get();
  }
  queue<PII> q;
  q.push({0,0});
  d[0][0] = 0;
  while (!q.empty()) {
    int x = q.front().first, y = q.front().second;
    q.pop();
    for (int id = 0; id < 2; ++id) {
      for (int i = 1; i <= K ;++i) {
        int nx = x + dx[id] * i, ny = y + dy[id] * i;
        if (!in(nx, ny)) break;
        if (!g[nx][ny]) continue;
        if (d[nx][ny] == d[x][y]) break;
        if (d[nx][ny] == -1)
          d[nx][ny] = d[x][y] + 1,
          q.push({nx, ny});
      }
    }
  }
  //for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) printf("%d%c", d[i][j], " \n"[j==N -1]);
  printf("%d\n", d[N - 1][N - 1]);
}
