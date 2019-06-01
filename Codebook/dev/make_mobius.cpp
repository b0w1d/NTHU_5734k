template<typename T> vector<T> make_mobius(T limit) {
  auto is_prime = Eratosthenes_sieve(limit);
  vector<T> mobius(limit, 1);
  mobius[0] = 0;
  for (LL p = 2; p < limit; ++p) if (is_prime[p]) {
    for (LL n = p; n < limit; n += p)
      mobius[n] = -mobius[n];
    for (LL n = p * p; n < limit; n += p * p)
      mobius[n] = 0;
  }
  return mobius;
}