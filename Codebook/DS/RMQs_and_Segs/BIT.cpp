template<typename T>
struct BIT {
  int N = 1<<20;
  vector<T> F;
  BIT() { F.resize(1<<20); }
  void add(int i, T v) {
    ++i;
    for (; i < N; i += i & -i) F[i] += v;
  }
  T query(int i) {
    T ans = 0;
    for (; i; i ^= i & -i) ans += F[i];
    return ans;
  }
  T query(int i, int j) { return query(j) - query(i); }
  T operator[](size_t i) { return query(i, i + 1); }
};
