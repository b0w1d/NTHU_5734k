// To find min f(x, y) = a * x * x + b * x * y + c * y * y
// (x, y) <- Z^2 nonzero
// return (x, y)
 PLL form(LL a, LL b, LL c) {
  assert(b * b < 4 * a * c and a > 0);
  LL x, y;
  if (a > c) return tie(x, y) = form(c, b, a), {y, x};
  if (a == c and b < 0) return tie(x, y) = form(a, -b, c), {-x, y};
  if (b > a or b <= -a) {
    LL n = (a - b) / (2 * a), x, y;
    if (2 * a * n <= a - b) --n;
    tie(x, y) = form(a, 2 * a * n + b, a * n * n + b * n + c);
    return {x - n * y, y};
  }
  // 1 <= a <= c and -a < b <= a and (a == c implies b >= 0)
  return {1, 0};
}  
