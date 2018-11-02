template<typename R> // return_type
struct MongeDP { // NOTE: if update like rolling dp, then enclose dp value in wei function and remove dp[] in R.H.S when updating stuff
  int n;
  vector<R> dp;
  vector<int> pre;
  function<bool(R, R)> cmp; // true is left better
  function<R(int, int)> w;  // w(i, j) = cost(dp[i] -> dp[j]) 
  MongeDP(int _n, function<bool(R, R)> c, function<R(int, int)> get_cost)
      : n(_n), dp(n + 1), pre(n + 1, -1), cmp(c), w(get_cost) {
    deque<tuple<int, int, int>> dcs; // decision
    dcs.emplace_back(0, 1, n); // transition from dp[0] is effective for [1, N]
    for (int i = 1; i <= n; ++i) {
      while (get<2>(dcs.front()) < i) dcs.pop_front(); // right bound is out-dated
      pre[i] = get<0>(dcs.front());
      dp[i] = dp[pre[i]] + w(pre[i], i); // best t is A[dcs.top(), i)
      while (dcs.size()) {
        int x, lb, rb;
        tie(x, lb, rb) = dcs.back();
        if (lb <= i) break; // will be pop_fronted soon anyway
        if (!cmp(dp[x] + w(x, lb), dp[i] + w(i, lb))) {
          dcs.pop_back();
          if (dcs.size()) get<2>(dcs.back()) = n;
        } else break;
      }
      int best = -1;
      for (int lb = i + 1, rb = n, x = get<0>(dcs.back()); lb <= rb; ) {
        int mb = lb + rb >> 1;
        if (cmp(dp[i] + w(i, mb), dp[x] + w(x, mb))) {
          best = mb;
          rb = mb - 1;
        } else lb = mb + 1;
      }
      if (~best) {
        get<2>(dcs.back()) = best - 1;
        dcs.emplace_back(i, best, n);
      }
    }
  }
  void ensure_monge_condition() {
    // Monge Condition: i <= j <= k <= l then w(i, l) + w(j, k) >(<)= w(i, k) + w(j, l)
    for (int i = 0; i <= n; ++i)
      for (int j = i; j <= n; ++j)
        for (int k = j; k <= n; ++k)
          for (int l = k; l <= n; ++l) {
            R w0 = w(i, l), w1 = w(j, k), w2 = w(i, k), w3 = w(j, l);
            assert(w0 + w1 >= w2 + w3); // if maximization, revert the sign
          }
  }
  R operator[](int x) { return dp[x]; }
};

/* Example:
  MongeDP<int64_t> mdp(N, [](int64_t x, int64_t y) { return x < y; },
                       [&](int x, int rb) {
                         auto abscub = [](int64_t x) { return abs(x * x * x); };
                         return abscub(A[rb - 1] - X[x]) + abscub(Y[x]);
                       });
  // mdp.ensure_monge_condition();
  
OR in case rolling dp, remember to remove dp[] in R.H.S. in lines 15, 20, 28 and do the following:
  vector<int64_t> dp(N + 1, 1LL << 60);
  dp[0] = 0;
  for (int i = 1; i < G + 1; ++i) {
    dp = MongeDP<int64_t>(N, [](int64_t x, int64_t y) { return x < y; },
                         [&](int x, int rb) {
                           return dp[x] + cost[x][rb];
                         }).dp;
  }

*/
