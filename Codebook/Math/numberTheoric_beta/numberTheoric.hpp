template<typename F> tuple<F, F, F> ext_gcd(F a, F b);
template<typename F> F powM(F x, F p, F mod);
template<typename F> F dangerous_mul(F a, F b, F mod);
template<typename F> vector<F> linear_inv(F p, int k);
namespace LLFactorization {
  typedef long long LL;
  LL LLmul(LL x, LL y, LL mod);
  LL powM(LL x, LL p, LL mod);
  bool miller_rabin(LL n, int s = 7);
  LL pollard_rho(LL n);
  template<typename F> vector<pair<F, int>> factor(F m);
} // namespace LLFactorization
template<typename F> F phi(F m);
template<typename F> F order(F x, F m);
template<typename F> F cycles(F a, F m);
template<typename F> F generator(F p);
template<typename F> F discrete_log(F b, F n, F M);
template<typename F> F discrete_kth_root(F k, F m, F p);

