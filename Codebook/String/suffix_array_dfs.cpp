pair<int, int> f(int l, int r, int d, int k) {
// return {the_jth_suffix, length}
// to find the kth suffix (0 - index) 
  while (sa[l] + d >= n and l < r) ++l;
  for (int i = l; i < r; ++i) {
    int j = i;
    LL total = 0;
    while (j < r and sa[j] + d < n and s[sa[j] + d] == s[sa[i] + d]) 
      total += n - sa[j++] - d;
    if (j - i > k) return {sa[i], d};
    else if (total <= k) k -= total;
    else return f(i, j, d + 1, k - (j - i));
    i = j - 1;
  }
  assert(0);
}
