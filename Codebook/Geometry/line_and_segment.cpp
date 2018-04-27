pt A[100], B[100];
pair<double, double> solve(line a, line b, double t) {
  pt point_a = a.first, point_b = b.first, speed_a = a.second, speed_b = b.second;
  double ansl = 1e18, ansr = -1e18;
  auto upd = [&] (pt a) { ansl = min(ansl, abs(a)), ansr = max(ansr, abs(a));};
  pt diff_dist = point_a - point_b;
  pt diff_speed = speed_a - speed_b;
  upd(diff_dist);          
  upd(diff_dist + t * diff_speed);
  if (norm(diff_speed) > eps) {
    auto mt = -dot(diff_dist, diff_speed) / norm(diff_speed);
    if (0 < mt and mt < t) 
      upd(diff_dist + diff_speed * mt);
  }
  return {ansl, ansr};
}
int main() {
  int x, y, T, a, b; scanf("%d", &T);
  for (int t = 0; t < T; ++t) {
    double va, vb;
    scanf("%d%d", &a, &b);
    for (int i = 0; i < a; ++i) 
      scanf("%d%d", &x, &y), A[i] = pt(x, y), va += i? abs(A[i] - A[i - 1]): 0;
    for (int i = 0; i < b; ++i) 
      scanf("%d%d", &x, &y), B[i] = pt(x, y), vb += i? abs(B[i] - B[i - 1]): 0;
    pt cura = A[0], curb = B[0];
    double ansl = 1e18, ansr = -1e18;
 
