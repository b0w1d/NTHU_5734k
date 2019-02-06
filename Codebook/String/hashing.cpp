const int primes[10] = {1000010483, 1000010503, 1000010513, 1000010549, 1000010593, 1000010597, 1000010611, 1000010633, 1000010659, 1000010699};
template<class F>
struct Hashing { // As default, SIGMA = [a-z]
  vector<int> H, q_inv;
  int MOD, Q;
  Hashing() {}
  Hashing(F s, int P, int Q = 256) : MOD(P), Q(Q) {
    function<int(int)> inv = [&](int a) {
      return a == 1 ? 1 : 1ll * (MOD - MOD / a) * inv(MOD % a) % MOD;
    };
    const int n = s.size(), invQ = inv(Q);
    H.assign(n + 1, 0), q_inv.resize(n + 1), q_inv[0] = 1;
    partial_sum(q_inv.begin(), q_inv.end(), q_inv.begin(), [&](int prev, int _) {
      return 1ll * prev * invQ % MOD;
    });
    for (int i = 0, col = 1; i < n; ++i, col = 1ll * col * Q % P)
      H[i + 1] = (H[i] + 1ll * col * s[i]) % P;
  }
  int get_hash(int l, int r) { // [l, r)
    return 1ll * (MOD + H[r] - H[l]) * q_inv[l] % MOD;
  }
};
