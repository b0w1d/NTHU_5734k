// SIGMA[0] will not be considered
const string SIGMA = "_0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
vector<int> INV_SIGMA;
const int SGSZ = 63;

struct PMA {
  PMA *next[SGSZ];  // next[0] is for fail
  vector<int> ac;
  PMA *last; // state of longest accepted string that is pre of this
  PMA() : last(nullptr) { fill(next, next + SGSZ, nullptr); }
};

template<typename T>
PMA *buildPMA(const vector<T> &p) {
  PMA *root = new PMA;
  for (int i = 0; i < p.size(); ++i) {  // make trie
    PMA *t = root;
    for (int j = 0; j < p[i].size(); ++j) {
      int c = INV_SIGMA[p[i][j]];
      if (t->next[c] == nullptr) t->next[c] = new PMA;
      t = t->next[c];
    }
    t->ac.push_back(i);
  }
  queue<PMA *> que;  // make failure link using bfs
  for (int c = 1; c < SGSZ; ++c) {
    if (root->next[c]) {
      root->next[c]->next[0] = root;
      que.push(root->next[c]);
    } else root->next[c] = root;
  }
  while (!que.empty()) {
    PMA *t = que.front();
    que.pop();
    for (int c = 1; c < SGSZ; ++c) {
      if (t->next[c]) {
        que.push(t->next[c]);
        PMA *r = t->next[0];
        while (!r->next[c]) r = r->next[0];
        t->next[c]->next[0] = r->next[c];
        t->next[c]->last = r->next[c]->ac.size() ? r->next[c] : r->next[c]->last;
      }
    }
  }
  return root;
}

void destructPMA(PMA *root) {
  queue<PMA *> que;
  que.emplace(root);
  while (!que.empty()) {
    PMA *t = que.front();
    que.pop();
    for (int c = 1; c < SGSZ; ++c) {
      if (t->next[c] && t->next[c] != root) que.emplace(t->next[c]);
    }
    delete t;
  }
}

template<typename T>
map<int, int> match(const T &t, PMA *v) {
  map<int, int> res;
  for (int i = 0; i < t.size(); ++i) {
    int c = INV_SIGMA[t[i]];
    while (!v->next[c]) v = v->next[0];
    v = v->next[c];
    for (int j = 0; j < v->ac.size(); ++j) ++res[v->ac[j]];
    for (PMA *q = v->last; q; q = q->last) {
      for (int j = 0; j < q->ac.size(); ++j) ++res[q->ac[j]];
    }
  }
  return res;
}

signed main() {
  INV_SIGMA.assign(256, -1);
  for (int i = 0; i < SIGMA.size(); ++i) {
    INV_SIGMA[SIGMA[i]] = i;
  }

}
