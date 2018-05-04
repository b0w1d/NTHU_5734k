namespace geo {
  using pt = complex<double>;
  using cir = pair<pt, double>;
  pt get_pt() { static double a, b; scanf("%lf%lf", &a, &b); return geo::pt(a, b);};
  const double EPS = 1e-4;
  const double PI = acos(-1);
  pt cent(cir C) { return C.first; }
  double radi(cir C) { return C.second; }
  int dcmp(double x) { return abs(x) < EPS ? 0 : x > 0 ? 1 : -1; }
  bool less(pt a, pt b) { return real(a) < real(b) || real(a) == real(b) && imag(a) < imag(b); }
  bool more(pt a, pt b) { return real(a) > real(b) || real(a) == real(b) && imag(a) > imag(b); }
  double dot(pt a, pt b) { return real(conj(a) * b); }
  double cross(pt a, pt b) { return imag(conj(a) * b); }
  double sarea(pt a, pt b, pt c) { return cross(b - a, c - a); }
  double area(cir c) { return radi(c) * radi(c) * PI; }
  int ori(pt a, pt b, pt c) { return dcmp(sarea(a, b, c)); }
  double angle(pt a, pt b) { return acos(dot(a, b) / abs(a) / abs(b)); }
  pt rotate(pt a, double rad) { return a * pt(cos(rad), sin(rad)); }
  pt normal(pt a) { return pt(-imag(a) / abs(a), real(a) / abs(a)); }
  pt normalized(pt a) { return a / abs(a); }

  pt get_line_intersection(pt p, pt v, pt q, pt w) {
    // L = p + t * v, J = q + s * w
    assert(dcmp(cross(v, w)));
    return p + v * cross(w, p - q) / cross(v, w);
  }
  double distance_to_line(pt p, pt a, pt b) {
    // the line contains two distinct points a, b
    return abs(cross(b - a, p - a) / abs(b - a));
  }
  double distance_to_segment(pt p, pt a, pt b) {
    // similar to previous function
    if (a == b) return abs(p - a);
    pt v1(b - a), v2(p - a), v3(p - b);
    if (dcmp(dot(v1, v2)) < 0) return abs(v2);
    else if (dcmp(dot(v1, v3)) > 0) return abs(v3);
    return abs(cross(v1, v2)) / abs(v1);
  }
  pt get_line_projection(pt p, pt a, pt b) {
    pt v = b - a;
    return a + dot(v, p - a) / dot(v, v) * v;
  }
  bool segment_proper_intersection(pt a1, pt a2, pt b1, pt b2) {
    double det1 = ori(a1, a2, b1) * ori(a1, a2, b2);
    double det2 = ori(b1, b2, a1) * ori(b1, b2, a2);
    return det1 < 0 && det2 < 0;
  }
  double area(vector<pt> p) {
    double area = 0;
    for (int i = 1; i < p.size() - 1; ++i) {
      area += sarea(p[0], p[i], p[i + 1]);
    }
    return area / 2;
  }
  bool is_point_on_segment(pt p, pt a1, pt a2) {
    return dcmp(sarea(p, a1, a2)) == 0 && dcmp(dot(a1 - p, a2 - p)) < 0;
  }
  int is_point_in_polygon(pt p, vector<pt> gon) {
    int wn = 0;
    int n = gon.size();
    for (int i = 0; i < n; ++i) {
      if (is_point_on_segment(p, gon[i], gon[(i + 1) % n])) return -1;
      int k = dcmp(cross(gon[(i + 1) % n] - gon[i], p - gon[i]));
      int d1 = dcmp(imag(gon[i]) - imag(p));
      int d2 = dcmp(imag(gon[(i + 1) % n] - imag(p)));
      wn += k > 0 && d1 <= 0 && d2 > 0;
      wn -= k < 0 && d2 <= 0 && d1 > 0;
    }
    return wn != 0;
  }
  vector<pt> convex_hull(vector<pt> p) {
    sort(p.begin(), p.end(), less);
    p.erase(unique(p.begin(), p.end()), p.end());
    int n = p.size(), m = 0;
    vector<pt> ch(n + 1);
    for (int i = 0; i < n; ++i) { // note that border is cleared
      while (m > 1 && ori(ch[m - 2], ch[m - 1], p[i]) <= 0) --m;
      ch[m++] = p[i];
    }
    for (int i = n - 2, k = m; i >= 0; --i) {
      while (m > k && ori(ch[m - 2], ch[m - 1], p[i]) <= 0) --m;
      ch[m++] = p[i];
    }
    ch.erase(ch.begin() + m - (n > 1), ch.end());
    return ch;
  }
  cir circumscribed_circle(vector<pt> tri) {
    pt B = tri[1] - tri[0];
    pt C = tri[2] - tri[0];
    double det = 2 * cross(B, C);
    pt r = pt(imag(C) * norm(B) - imag(B) * norm(C),
              real(B) * norm(C) - real(C) * norm(B)) / det;
    return {r + tri[0], abs(r)};
  }
  cir inscribed_circle(vector<pt> tri) {
    assert(tri.size() == 3);
    pt ans = 0;
    double div = 0;
    for (int i = 0; i < 3; ++i) {
      double l = abs(tri[(i + 1) % 3] - tri[(i + 2) % 3]);
      ans += l * tri[i], div += l;
    }
    ans /= div;
    return {ans, distance_to_line(ans, tri[0], tri[1])};
  }
  vector<pt> tangent_line_through_point(cir c, pt p) {
    if (dcmp(abs(cent(c) - p) - radi(c)) < 0) return {};
    else if (dcmp(abs(cent(c) - p) - radi(c)) == 0) return {p};
    auto theta = acos(radi(c) / abs(cent(c) - p));
    auto norm_v = normalized(p - cent(c));
    return {cent(c) + radi(c) * rotate(norm_v, +theta),
            cent(c) + radi(c) * rotate(norm_v, -theta)};
  }
  vector<pt> get_line_circle_intersection(cir d, pt st, pt ed) {
    pt v = ed - st, p = st - cent(d);
    double r = radi(d), a = norm(v), b = 2 * dot(p, v), c = norm(p) - r * r;
    double det = b * b - 4 * a * c;
    // t^2 * norm(v) + 2 * t * dot(p, v) + norm(p) - r * r = 0
    auto get_point = [=](double t) { return st + t * v; };
    if (dcmp(det) < 0) return {};
    if (dcmp(det) == 0) return {get_point(-b / 2 / a)};
    return {get_point((-b + sqrt(det)) / 2 / a),
            get_point((-b - sqrt(det)) / 2 / a)};
  }
  vector<pt> get_circle_circle_intersection(cir c, cir d) {
    auto a = cent(c), b = cent(d);
    auto r = radi(c), s = radi(d), g = abs(a - b);
    if (dcmp(g) == 0) return {}; // may be C == D
    if (dcmp(r + s - g) < 0 or dcmp(abs(r - s) - g) > 0) return {};
    auto C_to_D = normalized(b - a);
    auto theta = acos((r * r + g * g - s * s) / (2 * r * g));
    if (dcmp(theta) == 0) return {a + r * C_to_D};
    else return {a + rotate(r * C_to_D, theta), a + rotate(r * C_to_D, -theta)};
  }
  cir min_circle_cover(vector<pt> A) {
    random_shuffle(A.begin(), A.end());
    assert(A.size());
    cir ans = {A[0], 0};
    auto is_incir = [&](pt a) { return dcmp(abs(cent(ans) - a) - radi(ans)) < 0; };
    for (int i = 1; i < A.size(); ++i) if (not is_incir(A[i])) {
      ans = {A[i], 0};
      for (int j = 0; j < i; ++j) if (not is_incir(A[j])) {
        ans = {(A[i] + A[j]) / 2., abs(A[i] - A[j]) / 2};
        for (int k = 0; k < j; ++k) if (not is_incir(A[k])) 
          ans = circumscribed_circle({A[i], A[j], A[k]});
      }
    }
    return ans;
  }
};
