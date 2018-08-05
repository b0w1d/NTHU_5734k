vector<int> Prufer_encode(vector<vector<int>> T) {
  int n = T.size();
  assert(n > 1);
  vector<int> deg(n), code;
  priority_queue<int, vector<int>, greater<int>> pq;
  for (int i = 0; i < n; ++i) {
    deg[i] = T[i].size();
    if (deg[i] == 1) pq.push(i);
  }
  while (code.size() < n - 2) {
    int v = pq.top(); pq.pop();
    --deg[v];
    for (int u: T[v]) {
      if (deg[u]) {
        --deg[u], code.push_back(u); 
        if (deg[u] == 1) pq.push(u);
      }
    }
  }
  return code;
}

vector<vector<int>> Prufer_decode(vector<int> C) {
  int n = C.size() + 2;
  vector<vector<int>> T(n, vector<int>(0));
  vector<int> deg(n - 1, 0); // outdeg
  for (int c: C) ++deg[c];
  set<int> S; 
  for (int i = 0; i < n - 1; ++i) 
    if (not deg[i]) S.insert(i);
  for (int c: C) {
    int v = *S.begin(); S.erase(S.begin());
    T[v].push_back(c), T[c].push_back(v);
    --deg[c];
    if (not deg[c]) S.insert(c);
  }
  return T;
}
