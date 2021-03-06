vector<LL> fast_OR_transform(vector<LL> f, bool inverse) {
  for (int i = 0; (2 << i) <= f.size(); ++i)
    for (int j = 0; j < f.size(); j += 2 << i)
      for (int k = 0; k < (1 << i); ++k)
        f[j + k + (1 << i)] += f[j + k] * (inverse? -1 : 1);
  return f;
}
vector<LL> rev(vector<LL> A) {
  for (int i = 0; i < A.size(); i += 2) swap(A[i], A[i ^ (A.size() - 1)]);
  return A;
}
vector<LL> fast_AND_transform(vector<LL> f, bool inverse) {
  return rev(fast_OR_transform(rev(f), inverse));
}
vector<LL> fast_XOR_transform(vector<LL> f, bool inverse) {
  for (int i = 0; (2 << i) <= f.size(); ++i) 
    for (int j = 0; j < f.size(); j += 2 << i) 
      for (int k = 0; k < (1 << i); ++k) {
        int u = f[j + k], v = f[j + k + (1 << i)];
        f[j + k + (1 << i)] = u - v, f[j + k] = u + v;
      }
  if (inverse) for (auto &a : f) a /= f.size();
  return f;
}