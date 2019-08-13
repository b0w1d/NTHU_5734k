/* p == (a << n) + 1
   g = pow(root, (p - 1) / n)
   n    1<<n        p          a    root
   5    32          97         3    5
   6    64          193        3    5
   7    128         257        2    3
   8    256         257        1    3
   9    512         7681       15   17
   10   1024        12289      12   11
   11   2048        12289      6    11
   12   4096        12289      3    11
   13   8192        40961      5    3
   14   16384       65537      4    3
   15   32768       65537      2    3
   16   65536       65537      1    3
   17   131072      786433     6    10
   18   262144      786433     3    10 (605028353, 2308, 3)
   19   524288      5767169    11   3
   20   1048576     7340033    7    3
   20   1048576     998244353  952  3
   21   2097152     23068673   11   3
   22   4194304     104857601  25   3
   23   8388608     167772161  20   3
   24   16777216    167772161  10   3
   25   33554432    167772161  5    3 (1107296257, 33, 10)
   26   67108864    469762049  7    3
*/

// w = root^a mod p for NTT
// w = exp(-complex<double>(0, 2) * PI / N) for FFT

template<typename F = complex<double>>
void FFT(vector<F> &P, F w, bool inv = 0) {
  int n = P.size();
  int lg = __builtin_ctz(n);
  assert(__builtin_popcount(n));

  for (int j = 1, i = 0; j < n - 1; ++j) {
    for (int k = n >> 1; k > (i ^= k); k >>= 1);
    if (j < i) swap(P[i], P[j]);
  } //bit reverse

  vector<F> ws = {inv ? F{1} / w : w};
  for (int i = 1; i < lg; ++i) ws.push_back(ws[i - 1] * ws[i - 1]);
  reverse(ws.begin(), ws.end());

  for (int i = 0; i < lg; ++i) {
    for (int k = 0; k < n; k += 2<<i) {
      F base = F{1};
      for (int j = k; j < k + (1<<i); ++j, base = base * ws[i]) {
        auto t = base * P[j + (1<<i)];
        auto u = P[j];
        P[j] = u + t;
        P[j + (1<<i)] = u - t;
      }
    }
  }

  if (inv) for_each(P.begin(), P.end(), [&](F& a) { a = a / F(n); });
} //faster performance with calling by reference
