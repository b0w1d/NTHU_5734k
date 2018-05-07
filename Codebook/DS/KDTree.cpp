#include <bits/stdc++.h>
using namespace std;

struct KDNode {
  vector<int> v;
  KDNode *lc, *rc;
  KDNode(const vector<int> &_v) : v(_v), lc(nullptr), rc(nullptr) {}
  static KDNode *buildKDTree(vector<vector<int>> &pnts, int lb, int rb, int dpt) {
    if (rb - lb < 1) return nullptr;
    int axis = dpt % pnts[0].size();
    int mb = lb + rb >> 1;
    nth_element(pnts.begin() + lb, pnts.begin() + mb, pnts.begin() + rb, [&](const vector<int> &a, const vector<int> &b) {
      return a[axis] < b[axis];
    });
    KDNode *t = new KDNode(pnts[mb]);
    t->lc = buildKDTree(pnts, lb, mb, dpt + 1);
    t->rc = buildKDTree(pnts, mb + 1, rb, dpt + 1);
    return t;
  }
  static void release(KDNode *t) {
    if (t->lc) release(t->lc);
    if (t->rc) release(t->rc);
    delete t;
  }
  static void searchNearestNode(KDNode *t, KDNode *q, KDNode *&c, int dpt) {
    int axis = dpt % t->v.size();
    if (t->v != q->v && (c == nullptr || dis(q, t) < dis(q, c))) c = t;
    if (t->lc && (!t->rc || q->v[axis] < t->v[axis])) {
      searchNearestNode(t->lc, q, c, dpt + 1);
      if (t->rc && (c == nullptr || 1LL * (t->v[axis] - q->v[axis]) * (t->v[axis] - q->v[axis]) < dis(q, c))) {
        searchNearestNode(t->rc, q, c, dpt + 1);
      }
    } else if (t->rc) {
      searchNearestNode(t->rc, q, c, dpt + 1);
      if (t->lc && (c == nullptr || 1LL * (t->v[axis] - q->v[axis]) * (t->v[axis] - q->v[axis]) < dis(q, c))) {
        searchNearestNode(t->lc, q, c, dpt + 1);
      }
    }
  }
  static int64_t dis(KDNode *a, KDNode *b) {
    int64_t r = 0;
    for (int i = 0; i < a->v.size(); ++i) {
      r += 1LL * (a->v[i] - b->v[i]) * (a->v[i] - b->v[i]);
    }
    return r;
  }
};

signed main() {
  ios::sync_with_stdio(false);
  int T;
  cin >> T;
  for (int ti = 0; ti < T; ++ti) {
    int N;
    cin >> N;
    vector<vector<int>> pnts(N, vector<int>(2));
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < 2; ++j) {
        cin >> pnts[i][j];
      }
    }
    vector<vector<int>> _pnts = pnts;
    KDNode *root = KDNode::buildKDTree(_pnts, 0, pnts.size(), 0);
    for (int i = 0; i < N; ++i) {
      KDNode *q = new KDNode(pnts[i]);
      KDNode *c = nullptr;
      KDNode::searchNearestNode(root, q, c, 0);
      cout << KDNode::dis(c, q) << endl;
      delete q;
    }
    KDNode::release(root);
  }
  return 0;
}
