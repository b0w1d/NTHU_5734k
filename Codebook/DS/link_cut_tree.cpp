const int MEM = 1<<18;
struct Node {
  static Node mem[MEM], *pmem;
  Node *ch[2], *f;
  int id, size, revTag = 0, val = 0, sum = 0;
  void reverse() { swap(ch[0], ch[1]), revTag ^= 1; }
  void push() {
    if (revTag) {
      for (int i : {0, 1}) if (ch[i]) ch[i]->reverse();
      revTag = 0;
    }
  }
  void pull() {
    size = (ch[0] ? ch[0]->size : 0) + (ch[1] ? ch[1]->size : 0) + 1;
    sum = val;
    for (int i : {0, 1}) if (ch[i]) ch[i]->f = this, sum ^= ch[i]->sum;
  }
  int dir() { return f->ch[1] == this; }
  Node () : id(-1), size(0) { f = ch[0] = ch[1] = nullptr; }
  Node (int id, int _val = 0) : id(id), size(1) {
    val = sum = _val;
    f = ch[0] = ch[1] = nullptr;
  }
  bool isRoot() {
    return f == nullptr or f->ch[dir()] != this;
  } // is root of current splay
  void rotate() {
    Node* u = f;
    f = u->f;
    if (not u->isRoot()) u->f->ch[u->dir()] = this;
    int d = this == u->ch[0];
    u->ch[!d] = ch[d], ch[d] = u;
    u->pull(), pull();
  }
  void splay() {
    auto v = this;
    if (v == nullptr) return;
    {
      vector<Node*> st;
      Node* u = v;
      st.push_back(u);
      while (not u->isRoot()) st.push_back(u = u->f);
      while (st.size()) st.back()->push(), st.pop_back();
    }
    while (not v->isRoot()) {
      Node* u = v->f;
      if (not u->isRoot()) {
        (((u->ch[0] == v) xor (u->f->ch[0] == u)) ? v : u)->rotate();
      }
      v->rotate();
    } v->pull();
  }
  // Splay feature above
  void access() {
    for (Node *u = nullptr, *v = this; v != nullptr; u = v, v = v->f)
      v->splay(), v->ch[1] = u, v->pull();
  }
  Node* findroot() {
    access(), splay();
    auto v = this;
    while (v->ch[0] != nullptr) v = v->ch[0];
    v->splay(); // for complexity assertion
    return v;
  }
  void makeroot() { access(), splay(), reverse(); }
  static void split(Node* x, Node* y) { x->makeroot(), y->access(), y->splay(); }
  static bool link(Node* x, Node* p) {
    x->makeroot();
    if (p->findroot() != x) return x->f = p, true;
    else return false;
  }
  static void cut(Node* x) { 
    x->access(), x->splay(), x->push(), x->ch[0] = x->ch[0]->f = nullptr;
  }
  static bool cut(Node* x, Node* p) { // make sure that p is above x
    auto rt = x->findroot();
    x->makeroot();
    bool test = false;
    if (p->findroot() == x and p->f == x and not p->ch[0]) {
      p->f = x->ch[1] = nullptr, x->pull();
      test = true;
    }
    rt->makeroot();
    return test;
  }
  static int path(Node* x, Node* y) { // sum of value on path x-y
    auto tmp = x->findroot();
    split(x, y);
    int ret = y->sum;
    tmp->makeroot();
    return ret;
  }
  static Node* lca(Node* x, Node* y) {
    x->access(), y->access();
    y->splay();
    if (x->f == nullptr) return x;
    else return x->f;
  }
} Node::mem[MEM], *Node::pmem = Node::mem;

Node* vt[MEM];
