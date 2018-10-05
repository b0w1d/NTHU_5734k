template<typename T, typename Real = double>
Poly<Real> halfplane_intersection(vector<Line<T, Real>> s) {
  sort(s.begin(), s.end());
  const Real eps = 1e-10;
  int n = 1;
  for (int i = 1; i < s.size(); ++i) {
    if ((s[i].vec()&s[n - 1].vec()) < eps or abs(s[i].vec()^s[n - 1].vec()) > eps)
      s[n++] = s[i];
  }
  s.resize(n);
  assert(n >= 3);
  deque<Line<T, Real>> q;
  deque<Pt<Real>> p;
  q.push_back(s[0]);
  q.push_back(s[1]);
  p.push_back(s[0].get_intersection(s[1]));
  for (int i = 2; i < n; ++i) {
    while (q.size() > 1 and s[i].ori(p.back()) < -eps)
      p.pop_back(), q.pop_back();
    while (q.size() > 1 and s[i].ori(p.front()) < -eps)
      p.pop_front(), q.pop_front();
    p.push_back(q.back().get_intersection(s[i]));
    q.push_back(s[i]);
  }
  while (q.size() > 1 and q.front().ori(p.back()) < -eps)
    q.pop_back(), p.pop_back();
  while (q.size() > 1 and q.back().ori(p.front()) < -eps)
    q.pop_front(), p.pop_front();
  p.push_back(q.front().get_intersection(q.back()));
  return Poly<Real>(vector<Pt<Real>>(p.begin(), p.end()));
}
