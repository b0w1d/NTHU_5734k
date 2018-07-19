bool is_degree_sequence(vector<LL> d) {
  if (accumulate(d.begin(), d.end(), 0ll)&1) return false;
  sort(d.rbegin(), d.rend());
  const int n = d.size();
  vector<LL> pre(n + 1, 0);
  for (int i = 0; i < n; ++i) pre[i + 1] += pre[i] + d[i];
  for (LL k = 0, j = 0; k < n; ++k) {
    while (j < n and (j <= k or d[j] < k)) ++j;
    if (pre[k + 1] > k * (k + 1) + pre[j] - pre[k + 1] + (k + 1) * (n - j))
      return false;
  }
  return true;
}
