template <typename T>
struct LIS { // STRICTLY INCREASING
  vector<T> A;
  int n;
  LIS(vector<T> _A) : A(_A) { n = A.size(); }
  vector<T> solve() {
    vector<int> pre(n), min_with;
    for (int i = 0; i < n; ++i) {
      if (min_with.empty() or A[min_with.back()] < A[i]) {
        pre[i] = min_with.empty() ? -1: min_with.back();
        min_with.push_back(i);
      }
      else {
        int j = upper_bound(min_with.begin(), min_with.end(), i, [&](int i, int k) { return A[i] < A[k]; }) - min_with.begin();
        pre[i] = j ? min_with[j - 1] : -1;
        min_with[j] = i;
      }
    }
    int cur = min_with.back();
    vector<T> lis;
    while (cur != -1) lis.push_back(A[cur]), cur = pre[cur];
    reverse(lis.begin(), lis.end());
    return lis;
  }
};
