/* p == (a << n) + 1
   n    1 << n      p          a     root
   5    32          97         3     5
   6    64          193        3     5
   7    128         257        2     3
   8    256         257        1     3
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
   21   2097152     23068673   11   3
   22   4194304     104857601  25   3
   23   8388608     167772161  20   3
   24   16777216    167772161  10   3
   25   33554432    167772161  5    3 (1107296257, 33, 10)
   26   67108864    469762049  7    3
   27   134217728   2013265921 15   31 */
LL root = 10, p = 785433, lg = 18, a = 3;
LL pow(LL x, int b) {
  LL s = 1, m = x % p;
  for (; b; m = m * m % p, b >>= 1)
    if (b&1) s = s * m % p;
  return s;
}
vector<LL> NTT(vector<LL> P, bool inv=0) {
  int n = P.size();
  for (int j = 1, i = 0; j < n - 1; j++) {
    for (int k = n >> 1; k > (i ^= k); k >>= 1);
    if (j < i) swap(a[i], a[j]);
  } //bit reverse
  LL root = pow(root, a * (inv? p - 2: 1));
  //root has order (1<<lg)
  for (int i = 1; i <= lg; ++i) {
    LL wm = powMod( root , 1<< ( MAXlg - i ),prime);//order is (1<<i)
    for(int k = 0 ; k < (1 << lgOfP); k += (1 << i)){
      LL base = 1;
      for(int j = 0 ; j < 1<<(i-1) ;++j){
        LL t = base * pointP[ k + j + (1 << ( i - 1 ))] % prime,
        u = pointP[k + j] % prime;
        base = base * wm % prime;
        P[k + j] = ( u + t ) % prime;
        P[k + j + (1 << ( i - 1 ))] = ( u - t + prime ) % prime;
      }
    }
  }
  if(inv){
    LL invN = powMod(1 << lgOfP, prime - 2, prime);
    for (int i = 0; i < n; ++i)
      P[i] = P[i] * invN % prime;
  }
}


