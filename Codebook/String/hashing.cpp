struct Hashing { // As default, SIGMA = [a-z]
  vector<LL> H, q_inv_pow;
  const LL primes[10] = {1730472629, 1730472637, 1730472673, 1730472677, 1730472697,
  1730472707, 1730472719, 1730472761, 1730472769, 1730472787};
  LL P, Q;
  Hashing() {}
  Hashing(string s, LL SIGMA_SIZE = 26) {
    int n = s.size();
    H.resize(n + 1), q_inv_pow.resize(n + 1);
    P = primes[rand() % 10], Q = SIGMA_SIZE + 1;
    q_inv_pow[0] = 1, q_inv_pow[1] = modpow(Q, P - 2, P);
    for (int i = 2; i <= n; ++i) q_inv_pow[i] = q_inv_pow[i - 1] * q_inv_pow[1] % P;
    for (LL i = 0, col = 1; i < n; ++i, col = col * Q % P)
      (H[i + 1] += (H[i] + (s[i] - 'a' + 1) * col)) %= P;
  }
  LL get_hash(int l, int r) { // [l, r)
    return (P + H[r] - H[l]) * q_inv_pow[l] % P;
  }
};
