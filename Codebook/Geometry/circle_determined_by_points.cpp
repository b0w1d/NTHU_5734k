pt centre(vector<pt> P) {
  if (P.size() == 2) return (P[0] + P[1]) / 2.;
  assert(P.size() == 3);
  if (abs(cross(P[0] - P[1], P[2] - P[1])) < 1e-7) return ok = 0, pt(0);
  double B = 0, C = 0, A = cross(P[0], P[1]) + cross(P[1], P[2]) + cross(P[2], P[0]);
  for (int i = 0; i < 3; ++i) {
    B += dot(P[i], P[i]) * (P[(i + 2) % 3].imag() - P[(i + 1) % 3].imag());
    C += dot(P[i], P[i]) * (P[(i + 1) % 3].real() - P[(i + 2) % 3].real());
  }
  return pt(-B / 2 / A, -C / 2 / A);
}
