class Rotating_axis{
  struct POINT{
    Pt<LL> p;
    int i;
  };
  struct LINE{
    Line<LL> L;
    int i, j;
    bool operator<(const LINE B) const { return (L.vec()^B.L.vec()) > 0; }
  };
  vector<POINT> Ps;
  vector<LINE> Ls;
  vector<int> idx_at;
  int n, lid = 0;
public:
  Rotating_axis(vector<Pt<LL>> V) {
    n = V.size();
    Ps.resize(n), idx_at.resize(n);
    for (int i = 0; i < n; ++i) Ps[i] = {V[i], i};
    for (int i = 0; i < n; ++i) for (int j = 0; j < i; ++j) {
      auto a = V[i], b = V[j], v = b - a;
      int ii = i, jj = j;
      if (v.y > 0 or (v.y == 0 and v.x > 0)) swap(a, b), swap(ii, jj);
      Ls.push_back({Line<LL>(a, b), ii, jj});
    }
    sort(Ls.begin(), Ls.end());
    sort(Ps.begin(), Ps.end(), [&](POINT A, POINT B) {
      auto a = A.p, b = B.p;
      LL det1 = Ls[0].L.ori(a), det2 = Ls[0].L.ori(b);
      return det1 == det2? ((a - b) & Ls[0].L.vec()) : det1 > det2;
    });
    for (int i = 0; i < n; ++i) idx_at[Ps[i].i] = i;
  }
  bool next_axis() {
    if (lid == Ls.size()) return false;
    int i = Ls[lid].i, j = Ls[lid].j, wi = idx_at[i], wj = idx_at[j];
    swap(Ps[wi], Ps[wj]);
    swap(idx_at[i], idx_at[j]);
    return ++lid, true;
  }
  Pt<LL> at(size_t i) { return Ps[i].p; }
  Line<LL> cur_line() { return Ls[lid].L; }
};
