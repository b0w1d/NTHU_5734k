// if f is add function: 
// low2high = true -> zeta(a)[s] = sum(a[t] for t in s) 
// low2high = false -> zeta(a)[t] = sum(a[s] for t in s)
// else if f is sub function, you get inverse zeta function
template<typename T>
vector<T> subset_zeta_transform(int n, vector<T> a, function<T(T, T)> f, bool low2high = true) {
  assert(a.size() == 1 << n);
  if (low2high) {
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < 1 << n; ++j)
        if (j >> i & 1)
          a[j] = f(a[j], a[j ^ 1 << i]);
  } else {
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < 1 << n; ++j)
        if (~j >> i & 1)
          a[j] = f(a[j], a[j | 1 << i]);
  }
  return a;
}