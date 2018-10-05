namespace geo {
  using pt = complex<double>;
  using cir = pair<pt, double>;
  using poly = vector<pt>;
  using line = pair<pt, pt>; // point to point
  using plane = pair<pt, pt>;
  pt get_pt() { static double a, b; cin >> a >> b; return geo::pt(a, b);};
  const double EPS = 1e-10;
  const double PI = acos(-1);
  pt cent(cir C) { return C.first; }
  double radi(cir C) { return C.second; }
  pt st(line H) { return H.first; }
  pt ed(line H) { return H.second; }
  pt vec(line H) { return ed(H) - st(H); }
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
  pt normal(pt a) { return pt(-imag(a), real(a)) / abs(a); }
  pt normalized(pt a) { return a / abs(a); }

  pt get_line_intersection(line A, line B) {
    pt p = st(A), v = vec(A), q = st(B), w = vec(B);
    return p + v * cross(w, p - q) / cross(v, w);
  }
  double distance_to_line(pt p, line B) {
    return abs(cross(vec(B), p - st(B)) / abs(vec(B)));
  }
  double distance_to_segment(pt p, line B) {
    pt a = st(B), b = ed(B), v1(vec(B)), v2(p - a), v3(p - b);
    // similar to previous function
    if (a == b) return abs(p - a);
    if (dcmp(dot(v1, v2)) < 0) return abs(v2);
    else if (dcmp(dot(v1, v3)) > 0) return abs(v3);
    return abs(cross(v1, v2)) / abs(v1);
  }
  pt get_line_projection(pt p, line(B)) {
    pt v = vec(B);
    return st(B) + dot(v, p - st(B)) / dot(v, v) * v;
  }
  bool is_segment_proper_intersection(line A, line B) {
    pt a1 = st(A), a2 = ed(A), b1 = st(B), b2 = ed(B);
    double det1 = ori(a1, a2, b1) * ori(a1, a2, b2);
    double det2 = ori(b1, b2, a1) * ori(b1, b2, a2);
    return det1 < 0 && det2 < 0;
  }
  double area(poly p) {
    if (p.size() < 3) return 0;
    double area = 0;
    for (int i = 1; i < p.size() - 1; ++i)
      area += sarea(p[0], p[i], p[i + 1]);
    return area / 2;
  }
  bool is_point_on_segment(pt p, line B) {
    pt a = st(B), b = ed(B);
    return dcmp(sarea(p, a, b)) == 0 && dcmp(dot(a - p, b - p)) < 0;
  }
  bool is_point_in_plane(pt p, line H) {
    return ori(st(H), ed(H), p) > 0;
  }
  bool is_point_in_polygon(pt p, poly gon) {
    int wn = 0;
    int n = gon.size();
    for (int i = 0; i < n; ++i) {
      if (is_point_on_segment(p, {gon[i], gon[(i + 1) % n]})) return true;
      if (not is_point_in_plane(p, {gon[i], gon[(i + 1) % n]})) return false;
    }
    return true;
  }
  poly convex_hull(vector<pt> p) {
    sort(p.begin(), p.end(), less);
    p.erase(unique(p.begin(), p.end()), p.end());
    int n = p.size(), m = 0;
    poly ch(n + 1);
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
  cir circumscribed_circle(poly tri) {
    pt B = tri[1] - tri[0];
    pt C = tri[2] - tri[0];
    double det = 2 * cross(B, C);
    pt r = pt(imag(C) * norm(B) - imag(B) * norm(C),
              real(B) * norm(C) - real(C) * norm(B)) / det;
    return {r + tri[0], abs(r)};
  }
  cir inscribed_circle(poly tri) {
    assert(tri.size() == 3);
    pt ans = 0;
    double div = 0;
    for (int i = 0; i < 3; ++i) {
      double l = abs(tri[(i + 1) % 3] - tri[(i + 2) % 3]);
      ans += l * tri[i], div += l;
    }
    ans /= div;
    return {ans, distance_to_line(ans, {tri[0], tri[1]})};
  }
  poly tangent_line_through_point(cir c, pt p) {
    if (dcmp(abs(cent(c) - p) - radi(c)) < 0) return {};
    else if (dcmp(abs(cent(c) - p) - radi(c)) == 0) return {p};
    double theta = acos(radi(c) / abs(cent(c) - p));
    pt norm_v = normalized(p - cent(c));
    return {cent(c) + radi(c) * rotate(norm_v, +theta),
            cent(c) + radi(c) * rotate(norm_v, -theta)};
  }
  vector<pt> get_line_circle_intersection(cir d, line B) {
    pt v = vec(B), p = st(B) - cent(d);
    double r = radi(d), a = norm(v), b = 2 * dot(p, v), c = norm(p) - r * r;
    double det = b * b - 4 * a * c;
    // t^2 * norm(v) + 2 * t * dot(p, v) + norm(p) - r * r = 0
    auto get_point = [=](double t) { return st(B)+ t * v; };
    if (dcmp(det) < 0) return {};
    if (dcmp(det) == 0) return {get_point(-b / 2 / a)};
    return {get_point((-b + sqrt(det)) / 2 / a),
            get_point((-b - sqrt(det)) / 2 / a)};
  }
  vector<pt> get_circle_circle_intersection(cir c, cir d) {
    pt a = cent(c), b = cent(d);
    double r = radi(c), s = radi(d), g = abs(a - b);
    if (dcmp(g) == 0) return {}; // may be C == D
    if (dcmp(r + s - g) < 0 or dcmp(abs(r - s) - g) > 0) return {};
    pt C_to_D = normalized(b - a);
    double theta = acos((r * r + g * g - s * s) / (2 * r * g));
    if (dcmp(theta) == 0) return {a + r * C_to_D};
    else return {a + rotate(r * C_to_D, theta), a + rotate(r * C_to_D, -theta)};
  }
  cir min_circle_cover(vector<pt> A) {
    random_shuffle(A.begin(), A.end());
    cir ans = {0, 0};
    auto is_incir = [&](pt a) { return dcmp(abs(cent(ans) - a) - radi(ans)) < 0; };
    for (int i = 0; i < A.size(); ++i) if (not is_incir(A[i])) {
      ans = {A[i], 0};
      for (int j = 0; j < i; ++j) if (not is_incir(A[j])) {
        ans = {(A[i] + A[j]) / 2., abs(A[i] - A[j]) / 2};
        for (int k = 0; k < j; ++k) if (not is_incir(A[k]))
          ans = circumscribed_circle({A[i], A[j], A[k]});
      }
    }
    return ans;
  }
  pair<pt, pt> closest_pair(vector<pt> &V, int l, int r) { // l = 0, r = V.size()
    pair<pt, pt> ret = {pt(-1e18), pt(1e18)};
    const auto upd = [&](pair<pt, pt> a) {
      if (abs(a.first - a.second) < abs(ret.first - ret.second)) ret = a;
    };
    if (r - l < 40) { // GOD's number! It performs well!
      for (int i = l; i < r; ++i) for (int j = l; j < i; ++j)
        upd({V[i], V[j]});
      return ret;
    }
    int m = l + r >> 1;
    const auto cmpy = [](pt a, pt b) { return imag(a) < imag(b); };
    const auto cmpx = [](pt a, pt b) { return real(a) < real(b); };
    nth_element(V.begin() + l, V.begin() + m, V.begin() + r, cmpx);
    pt mid = V[m];
    upd(closest_pair(V, l, m));
    upd(closest_pair(V, m, r));
    double delta = abs(ret.first - ret.second);
    vector<pt> spine;
    for (int k = l; k < r; ++k)
      if (abs(real(V[k]) - real(V[m])) < delta) spine.push_back(V[k]);
    sort(spine.begin(), spine.end(), cmpy);
    for (int i = 0; i < spine.size(); ++i)
      for (int j = i + 1; j - i < 8 and j < spine.size(); ++j) {
        upd({spine[i], spine[j]});
      }
    return ret;
  }
};
