template<typename D, D zero, typename Q, typename M>
vector<D> mos(const vector<D> &dat, vector<Q> q, M sum, function<void(M&, D, int)> fadd) {
  int bs = sqrt(q.size()) + 1;
  vector<D> ans(q.size(), zero);  
  vector<int> qord(q.size());
  iota(qord.begin(), qord.end(), 0);
  sort(qord.begin(), qord.end(), [&](int i, int j) {
    if (get<0>(q[i]) / bs != get<0>(q[j]) / bs) return get<0>(q[i]) < get<0>(q[j]);
    return get<1>(q[i]) < get<1>(q[j]);
  });
  for (int qi = 0, lb = 0, rb = 0; qi < q.size(); ++qi) { // [lb, rb)
    int i = qord[qi];
    while (get<0>(q[i]) < lb) fadd(sum, dat[--lb], 1);
    while (get<1>(q[i]) < rb) fadd(sum, dat[--rb], -1);
    while (lb < get<0>(q[i])) fadd(sum, dat[lb++], -1);
    while (rb < get<1>(q[i])) fadd(sum, dat[rb++], 1);
    ans[i] = get<0>(sum);
  }
  return ans;
}

/* example
using maintain_type = tuple<int64_t, array<int, 1 << 17>>;
auto mt_add = [&](maintain_type &s, int d, int sign) {
  int w = 0;
  for (int i = 0; i < 17; ++i) w += get<1>(s)[d ^ 1 << i];
  get<0>(s) += sign * w;
  get<1>(s)[d] += sign;
};
maintain_type mt_zero = make_tuple(0, array<int, 1 << 17>());
vector<int> res = mos<int, 0, tuple<int, int>, maintain_type>(dat, query, mt_zero, mt_add);
*/
