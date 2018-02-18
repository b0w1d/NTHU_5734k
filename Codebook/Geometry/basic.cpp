typedef complex<double> pt;
double cross(pt A, pt B) {
  return A.real() * B.imag() - A.imag() * B.real();
}
double dot(pt A, pt B) {
	return A.real() * B.real() + B.imag() * A.imag();
}
