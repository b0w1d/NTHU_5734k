#include <bits/stdc++.h>
using namespace std;
typedef complex<double> pt;
typedef pair<double, double> pdd;
typedef pair<pt, pt> line; // let C be the curve, (a, v) means a + tv <- C
const double eps = 1e-5;
double dot(pt a, pt b) { return real(conj(a) * b); };
double cross(pt a, pt b) { return imag(conj(a) * b); };
double angle(pt a, pt b) { return acos(dot(a, b) / abs(a) / abs(b)); }
bool pt_eq(pt a, pt b) { return abs(a - b) < eps; }
bool pt_cmp(pt a, pt b) { return pdd{real(a), imag(a)} < pdd{real(b), imag(b)}; }
pt normalized(pt a) { return a / abs(a); }

pt line_intersect(line a, line b) {
  pt ap = a.first, av = a.second, bp = b.first, bv = b.second;
  pt u = ap - bp;
  double t = cross(bv, u) / cross(av, bv);
  return ap + av * t;
}
bool is_seg_intersect(line a, line b) {
  pt as = a.first, ae = as + a.second,
     bs = b.first, be = bs + b.second;
  if (abs(cross(a.second, b.second)) <= eps) return false;
  double deta = cross(a.second, bs - as) * cross(a.second, be - as),
         detb = cross(b.second, as - bs) * cross(b.second, ae - bs);
  return deta < eps and detb < eps;
}
bool is_on_seg(line l, pt p) {
  pt s = l.first, t = l.second + s;
  return abs(cross(s - p, t - p)) < eps and dot(s - p, t - p) < 0;
}

