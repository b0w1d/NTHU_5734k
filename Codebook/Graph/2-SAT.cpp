#include <cstdio>
#include <vector>
#include <stack>
#include <cstring>
using namespace std;

const int N = 2010;
struct two_SAT {
  int n;
  vector<int> G[N], revG[N];
  stack<int> finish;
  bool sol[N], visit[N];
  int cmp[N];
  void init(int _n) {
    n = _n;
    for (int i = 0; i < N; i++) {
      G[i].clear();
      revG[i].clear();
    }
  }
  void add_edge(int u, int v) {
    // 2 * i -> i is True, 2 * i + 1 -> i is False
    G[u].push_back(v);
    G[v^1].push_back(u^1);
    revG[v].push_back(u);
    revG[u^1].push_back(v^1);
  }
  void dfs(int v) {
    visit[v] = true;
    for ( auto i:G[v] ) {
      if ( !visit[i] ) dfs(i);
    }
    finish.push(v);
  }
  void revdfs(int v, int id) {
    visit[v] = true;
    for ( auto i:revG[v] ) {
      if ( !visit[i] ) revdfs(i,id);
    }
    cmp[v] = id;
  }
  int scc() {
    memset( visit, 0, sizeof(visit) );
    for (int i = 0; i < 2 * n; i++) {
      if ( !visit[i] ) dfs(i);
    }
    int id = 0;
    memset( visit, 0, sizeof(visit) );
    while ( !finish.empty() ) {
      int v = finish.top(); finish.pop();
      if ( visit[v] ) continue;
      revdfs(v,++id);
    }
    return id;
  }
  bool solve() {
    scc();
    for (int i = 0; i < n; i++) {
      if ( cmp[2*i] == cmp[2*i+1] ) return 0;
      sol[i] = ( cmp[2*i] > cmp[2*i+1] );
    }
    return 1;
  }
} sat;

int main() {
  // ( a or not b ) and ( b or c ) and ( not c or not a )
  sat.init(3);
  sat.add_edge( 2*0+1, 2*1+1 );
  sat.add_edge( 2*1+1, 2*2+0 );
  sat.add_edge( 2*2+0, 2*0+1 );
  printf("%d\n", sat.solve() );
  return 0;
}