namespace kika {
typedef complex<double> cod;
const double EPS = 1e-9;
const double PI = acos(-1);
int dcmp(double x) {
  if (abs(x) < EPS) return 0;
  return x > 0 ? 1 : -1;
}
bool less(cod a, cod b) { return real(a) < real(b) || (real(a) == real(b) && imag(a) < imag(b)); }
bool more(cod a, cod b) { return real(a) > real(b) || (real(a) == real(b) && imag(a) > imag(b)); }
double dot(cod a, cod b) { return real(conj(a) * b); }
double cross(cod a, cod b) { return imag(conj(a) * b); }
int ori(cod b, cod a, cod c) { return dcmp(cross(a - b, c - b)); }
double angle(cod a, cod b) { return acos(dot(a, b) / abs(a) / abs(b)); }
double sarea(cod a, cod b, cod c) { return cross(b - a, c - a); }
cod rotate(cod a, double rad) { return a * cod(cos(rad), sin(rad)); }
cod normal(cod a) { return cod(-imag(a) / abs(a), real(a) / abs(a)); }
cod get_line_intersection(cod p, cod v, cod q, cod w) {
  cod u(p - q);
  double t = cross(w, u) / cross(v, w);
  return p + v * t;
}
double distance_to_line(cod p, cod a, cod b) { return abs(cross(b - a, p - a) / abs(b - a)); }
double distance_to_segment(cod p, cod a, cod b) {
  if (a == b) return abs(p - a);
  cod v1(b - a), v2(p - a), v3(p - b);
  if (dcmp(dot(v1, v2)) < 0) return abs(v2);
  else if (dcmp(dot(v1, v3)) > 0) return abs(v3);
  return abs(cross(v1, v2)) / abs(v1);
}
cod get_line_projection(cod p, cod a, cod b) {
  cod v(b - a);
  return a + dot(v, p - a) / dot(v, v) * v;
}
bool segment_proper_intersection(cod a1, cod a2, cod b1, cod b2) {
  double c1 = cross(a2 - a1, b1 - a1), c2 = cross(a2 - a1, b2 - a1);
  double c3 = cross(b2 - b1, a1 - b1), c4 = cross(b2 - b1, a2 - b1);
  return dcmp(c1) * dcmp(c2) < 0 and dcmp(c3) * dcmp(c4) < 0;
}
double polygon_area(vector<cod> p) {
  double area = 0;
  for (int i = 1; i < int(p.size()) - 1; ++i) { area += cross(p[i] - p[0], p[i + 1] - p[0]); }
  return area / 2;
}
bool is_point_on_segment(cod p, cod a1, cod a2) {
  return dcmp(cross(a1 - p, a2 - p)) == 0 && dcmp(dot(a1 - p, a2 - p)) < 0;
}
int is_point_in_polygon(cod p, vector<cod> gon) {
  int wn = 0;
  int n = gon.size();
  for (int i = 0; i < n; ++i) {
    if (is_point_on_segment(p, gon[i], gon[(i + 1) % n])) return -1;
    int k = dcmp(cross(gon[(i + 1) % n] - gon[i], p - gon[i]));
    int d1 = dcmp(imag(gon[i]) - imag(p));
    int d2 = dcmp(imag(gon[(i + 1) % n] - imag(p)));
    wn += k > 0 and d1 <= 0 and d2 > 0;
    wn -= k < 0 and d2 <= 0 and d1 > 0;
  }
  return wn != 0;
}
vector<cod> convex_hull(vector<cod> p) {
  sort(p.begin(), p.end(), less);
  p.erase(unique(p.begin(), p.end()), p.end());
  int n = p.size(), m = 0;
  vector<cod> ch(n + 1);
  for (int i = 0; i < n; ++i) {
    while (m > 1 && dcmp(cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2])) <= 0) { --m; }
    ch[m++] = p[i];
  }
  for (int i = n - 2, k = m; i >= 0; --i) {
    while (m > k && dcmp(cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2])) <= 0) { --m; }
    ch[m++] = p[i];
  }
  ch.erase(ch.begin() + m - (n > 1), ch.end());
  return ch;
}
};  // namespace kika
