template<typename T>
T min_circle_cover(vector<complex<T>> p) {
  int n = p.size();
  random_shuffle(p.begin(), p.end());
  complex<T> c = p[0];
  T r = 0;
  for (int i = 1; i < n; ++i) {
    if (abs(p[i] - c) <= r) continue;
    c = p[i];
    r = 0;
    for (int j = 0; j < i; ++j) {
      if (abs(p[j] - c) <= r) continue;
      c = (p[i] + p[j]) / complex<T>(2, 0);
      r = abs(p[j] - c);
      for (int k = 0; k < j; ++k) {
        if (abs(p[k] - c) <= r) continue;
        c = [](complex<T> p0, complex<T> p1, complex<T> p2) {
          auto cross = [](complex<T> a, complex<T> b) { return imag(conj(a) * b); };
          auto dot = [](complex<T> a, complex<T> b) { return real(conj(a) * b); };
          complex<T> a1 = p1 - p0;
          complex<T> a2 = p2 - p0;
          complex<T> b1(real(a1), real(a2));
          complex<T> b2(imag(a1), imag(a2));
          complex<T> c(dot(a1, a1) / 2, dot(a2, a2) / 2);
          T d = cross(b1, b2);
          return complex<T>(real(p0) + cross(c, b2) / d, imag(p0) + cross(b1, c) / d);
        } (p[i], p[j], p[k]);
        r = abs(p[k] - c);
      }
    }
  }
  return r;
}
