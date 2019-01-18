bool Erdos_Gallai(vector<LL> d) {
  if (accumulate(d.begin(), d.end(), 0ll)&1) return false;
  sort(d.rbegin(), d.rend());
  const int n = d.size();
  vector<LL> pre(n + 1, 0);
  for (int i = 0; i < n; ++i) pre[i + 1] += pre[i] + d[i];
  for (int k = 1, j = n; k <= n; ++k) {
    while (k < j and (d[j - 1] <= k)) --j; // [0, k), > : [k, j), <= : [j, n)
    j = max(k, j);
    if (pre[k] > (LL)k * (k - 1) + pre[n] - pre[j] + (LL)k * (j - k))
      return false;
  }
  return true;
}
