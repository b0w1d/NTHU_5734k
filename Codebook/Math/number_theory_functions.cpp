vector<bool> Atkin_sieve(int limit) {
  assert(limit > 10 and limit <= 1e9);
  vector<bool> sieve(limit, false);
  sieve[2] = sieve[3] = true;
  for (int x = 1; x * x < limit; ++x)
    for (int y = 1; y * y < limit; ++y) {
      int n = (4 * x * x) + (y * y);
      if (n <= limit && (n % 12 == 1 || n % 12 == 5))
        sieve[n] = sieve[n] ^ true;
      n = (3 * x * x) + (y * y);
      if (n <= limit && n % 12 == 7)
        sieve[n] = sieve[n] ^ true;
      n = (3 * x * x) - (y * y);
      if (x > y && n <= limit && n % 12 == 11)
        sieve[n] = sieve[n] ^ true;
    }
  for (int r = 5; r * r < limit; ++r) if (sieve[r])
    for (int i = r * r; i < limit; i += r * r)
      sieve[i] = false;
  return sieve;
}
vector<bool> Eratosthenes_sieve(int limit) {
  assert(limit >= 10 and limit <= 1e9);
  vector<bool> sieve(limit, true);
  sieve[0] = sieve[1] = false;
  for (int p = 2; p * p < limit; ++p) if (sieve[p]) {
    for (int n = p * p; n < limit; n += p) sieve[n] = false;
  }
  return sieve;
}
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
