const int SIGMA = 256;

struct PMA {
  PMA *next[SIGMA];  // next[0] is for fail
  vector<int> ac;
  PMA() { fill(next, next + SIGMA, nullptr); }
};

template<typename T, int SLB = 'a', int SRB = 'z'>
PMA *buildPMA(const vector<T> &p) {
  PMA *root = new PMA;
  for (int i = 0; i < p.size(); ++i) {  // make trie
    PMA *t = root;
    for (int j = 0; j < p[i].size(); ++j) {
      int c = p[i][j];
      if (t->next[c] == nullptr) t->next[c] = new PMA;
      t = t->next[c];
    }
    t->ac.push_back(i);
  }
  queue<PMA *> que;  // make failure link using bfs
  for (int c = SLB; c <= SRB; ++c) {
    if (root->next[c]) {
      root->next[c]->next[0] = root;
      que.push(root->next[c]);
    } else root->next[c] = root;
  }
  while (!que.empty()) {
    PMA *t = que.front();
    que.pop();
    for (int c = SLB; c <= SRB; ++c) {
      if (t->next[c]) {
        que.push(t->next[c]);
        PMA *r = t->next[0];
        while (!r->next[c]) r = r->next[0];
        t->next[c]->next[0] = r->next[c];
      }
    }
  }
  return root;
}

template<typename T>
map<int, int> match(const T &t, PMA *v) {
  map<int, int> res;
  for (int i = 0; i < t.size(); ++i) {
    int c = t[i];
    while (!v->next[c]) v = v->next[0];
    v = v->next[c];
    for (int j = 0; j < v->ac.size(); ++j) ++res[v->ac[j]];
  }
  return res;
}
