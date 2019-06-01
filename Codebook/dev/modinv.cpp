int modinv(int a, int b = M, int x = 1, int y = 0) {
  if (b == 0) return x < 0 ? x + M : x;
  return modinv(b, a - a / b * b, y, x - a / b * y);
}