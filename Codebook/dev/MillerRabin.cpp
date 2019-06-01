    struct PrimeFactor {
      static long long mul(long long x, long long y, long long mod) {
        long long m = x, s = 0;
        for (; y; y >>= 1, m <<= 1, m = m >= mod ? m - mod : m)
          if (y & 1) s += m, s = s >= mod ? s - mod : s;
        return s;
      }
      static long long powmod(long long x, long long p, long long mod) {
        long long s = 1, m = x % mod;
        for (; p; m = mul(m, m, mod), p >>= 1)
          if (p & 1) s = mul(s, m, mod);
        return s;
      }
      static bool miller_rabin(long long n, int s = 7) {
        static const long long wits[7] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
        auto witness = [&](long long a, long long n, long long u, int t) {
          long long x = powmod(a, u, n), nx;
          for (int i = 0; i < t; ++i, x = nx) {
            nx = mul(x, x, n);
            if (nx == 1 && x != 1 && x != n - 1) return true;
          }
          return x != 1;
        };
        if (n < 2) return 0;
        if (~n & 1) return n == 2;
        long long u = n - 1, t = 0, a;
        for (; ~u & 1; u >>= 1) ++t;
        while (s--) if ((a = wits[s] % n) && witness(a, n, u, t)) return false;
        return true;
      }
    };