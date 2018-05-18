PLL CRT(PLL eq1, PLL eq2) {
  LL m1, m2, x1, x2;
  tie(x1, m1) = eq1, tie(x2, m2) = eq2;
  LL g = __gcd(m1, m2);
  if ((x1 - x2) % g) return {-1, 0}; // NO SOLUTION
  m1 /= g, m2 /= g;
  auto p = exd_gcd(m1, m2);
  LL lcm = m1 * m2 * g, res = mul(mul(p.first, (x2 - x1), lcm), m1, lcm) + x1;
  return {(res % lcm + lcm) % lcm, lcm};
}
