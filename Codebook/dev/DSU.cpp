struct DSU {
  vector<int> fa;
  vector<int> size;
  DSU(int n) : fa(n), size(n, 1) {
    iota(fa.begin(), fa.end(), 0);
  }
  int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
  }
  void merge(int x, int y) {
    int a = find(x);
    int b = find(y);
    if (a != b) {
      if (size[a] < size[b]) std::swap(a, b);
      fa[b] = a;
      size[a] += size[b];
    }
  }
};
