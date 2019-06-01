tuple<int, int, int> ext_gcd(int a, int b) {
  if (!b) return {1, 0, a};
  int x, y, g;
  tie(x, y, g) = ext_gcd(b, a % b);
  return {y, x - a / b * y, g};
}