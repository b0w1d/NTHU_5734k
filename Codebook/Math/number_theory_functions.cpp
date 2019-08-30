vector<int> linear_sieve(const int UPBD) {
  vector<int> primes, last_prime(UPBD, 0);
  for (int p = 2; p < UPBD; ++p) {
    if (not last_prime[p]) primes.push_back(p), last_prime[p] = p;
    for (int j = 0; primes[j] * p < UPBD; ++j) {
      last_prime[primes[j] * p] = primes[j];
      if (p % primes[j] == 0) break;
    }
  }
  return last_prime;
}
template<typename T> vector<T> make_mobius(T limit) {
  auto last_prime = linear_sieve(limit);
  vector<T> mobius(limit, 1);
  mobius[0] = 0;
  for (T p = 2; p < limit; ++p) {
    if (last_prime[p] == last_prime[p / last_prime[p]]) mobius[p] = 0;
    else mobius[p] = mobius[p / last_prime[p]] * -1;
  }
  return mobius;
}
