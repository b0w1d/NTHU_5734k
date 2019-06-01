template<typename T, T INF>
struct SegmentTreeBeats {
  vector<T> ext;      // extremum
  vector<T> h_ext;    // historic extremum
  vector<T> t_add;    // add tag
  vector<T> h_t_add;  // historic extremum on add tag
  vector<T> ext2;     // secondary extremum
  vector<T> t_add2;   // add tag on secondary extremum
  vector<T> h_t_add2; // historic extremum on add tag on secondary extremum
  function<T(T, T)> ext_func;
  SegmentTreeBeats(const vector<T> &arr, function<T(T, T)> _ext_func) : ext_func(_ext_func) {
    int n = 1 << 33 - __builtin_clz(arr.size());
    ext.resize(n);
    h_ext.resize(n);
    t_add.resize(n);
    h_t_add.resize(n);
    ext2.resize(n);
    t_add2.resize(n);
    h_t_add2.resize(n);
    function<void(int, int, int)> build = [&](int t, int lb, int rb) {
      if (rb - lb == 1) {
        ext[t] = arr[lb];
        h_ext[t] = arr[lb];
        ext2[t] = INF;
        return;
      }
      int mb = lb + rb >> 1;
      build(t << 1, lb, mb);
      build(t << 1 | 1, mb, rb);
      pull(t);
    };
    build(1, 0, arr.size());
  }
  void add(int t, int lb, int rb, int ql, int qr, T v) {
    if (qr <= lb || rb <= ql) return;
    if (ql <= lb && rb <= qr) {
      ext[t] += v;
      t_add[t] += v;
      ext2[t] += v;
      t_add2[t] += v;
      h_ext[t] = ext_func(h_ext[t], ext[t]);
      h_t_add[t] = ext_func(h_t_add[t], t_add[t]);
      h_t_add2[t] = ext_func(h_t_add2[t], t_add2[t]);
      ext2[t] = min(ext2[t], INF); // prevent overflow
      return;
    }
    push(t);
    int mb = lb + rb >> 1;
    add(t << 1, lb, mb, ql, qr, v);
    add(t << 1 | 1, mb, rb, ql, qr, v);
    pull(t);
  }
  void max_with(int t, int lb, int rb, int ql, int qr, T v) {
    if (qr <= lb || rb <= ql) return;
    if (ql <= lb && rb <= qr && v < ext2[t]) {
      if (ext[t] < v) {
        t_add[t] += v - ext[t];
        ext[t] = v;
      }
      return;
    }
    push(t);
    int mb = lb + rb >> 1;
    max_with(t << 1, lb, mb, ql, qr, v);
    max_with(t << 1 | 1, mb, rb, ql, qr, v);
    pull(t);
  }
  T query(int t, int lb, int rb, int ql, int qr, bool history = false) {
    if (qr <= lb || rb <= ql) return INF;
    if (ql <= lb && rb <= qr) return history ? h_ext[t] : ext[t];
    push(t);
    int mb = lb + rb >> 1;
    return ext_func(query(t << 1, lb, mb, ql, qr, history),
                    query(t << 1 | 1, mb, rb, ql, qr, history));
  }
  void pull(int t) {
    if (ext[t << 1] == ext[t << 1 | 1]) {
      ext[t] = ext[t << 1];
      ext2[t] = ext_func(ext2[t << 1], ext2[t << 1 | 1]);
    } else if (ext[t << 1] < ext[t << 1 | 1]) {
      ext[t] = ext[t << 1];
      ext2[t] = ext_func(ext2[t << 1], ext[t << 1 | 1]);
    } else {
      ext[t] = ext[t << 1 | 1];
      ext2[t] = ext_func(ext[t << 1], ext2[t << 1 | 1]);
    }
    h_ext[t] = ext_func(h_ext[t << 1], h_ext[t << 1 | 1]);
  }
  void push(int t) {
    auto pass = [&](int a, int b, bool has_ext) {
      T _t_add = t_add[a];
      T _h_t_add = h_t_add[a];
      if (!has_ext) {
        t_add[a] = t_add2[a];
        h_t_add[a] = h_t_add2[a];
      }
      h_ext[b] = ext_func(h_ext[b], ext[b] + h_t_add[a]);
      h_t_add[b] = ext_func(h_t_add[b], t_add[b] + h_t_add[a]);
      h_t_add2[b] = ext_func(h_t_add2[b], t_add2[b] + h_t_add2[a]);
      ext[b] += t_add[a];
      t_add[b] += t_add[a];
      ext2[b] += t_add2[a];
      t_add2[b] += t_add2[a];
      ext2[b] = min(ext2[b], INF); // prevent overflow
      t_add[a] = _t_add;
      h_t_add[a] = _h_t_add;
    };
    bool lmin = ext[t << 1] == ext_func(ext[t << 1], ext[t << 1 | 1]);
    bool rmin = ext[t << 1 | 1] == ext_func(ext[t << 1], ext[t << 1 | 1]);
    pass(t, t << 1, lmin);
    pass(t, t << 1 | 1, rmin);
    t_add[t] = 0;
    t_add2[t] = 0;
    h_t_add[t] = 0;
    h_t_add2[t] = 0;
  }
};
signed main() {
  SegmentTreeBeats<int, 0x7f7f7f7f> tree(A, [](int a, int b) { return min(a, b); });
    if (T == 1) {        // A[i] += C, for i in [L, R] 
      int C = fin.read_int();
      tree.add(1, 0, N, L - 1, R, C);
    } else if (T == 2) { // A[i] = max(A[i], D), for i in [L, R]
      int D = fin.read_int();
      tree.max_with(1, 0, N, L - 1, R, D);
    } else if (T == 3) { // min(A[i], for i in [L, R])
      printf("%d\n", tree.query(1, 0, N, L - 1, R));
    } else if (T == 4) { // min(A_historic[i], for i in [L, R])
      printf("%d\n", tree.query(1, 0, N, L - 1, R, true));
    } else assert(0);
}
