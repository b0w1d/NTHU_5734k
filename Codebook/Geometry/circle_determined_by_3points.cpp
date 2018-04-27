pt centre(vector<pt> P) {
  assert(P.size() == 3);
  auto A = (P[2] - P[0]) * i / pt(2), B = P[0] - P[1], C = P[2] - P[1];
  auto t = cross(A, C) / cross(B, C);
  return (P[0] + P[1]) / pt(2) + t * (P[1] - P[0]) * i;
}
