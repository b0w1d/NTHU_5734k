// -----------O(NlgNlgN)----------
pair<vector<int>, vector<int>> sa_db(const string s) {
  int n = s.size();
  vector<int> sa(n), ra(n), t(n);
  for (int i = 0; i < n; ++i) ra[sa[i] = i] = s[i];
  for (int h = 1; t[n - 1] != n - 1; h *= 2) {
    auto cmp = [&](int i, int j) {
      if (ra[i] != ra[j]) return ra[i] < ra[j];
      return i + h < n && j + h < n ? ra[i + h] < ra[j + h] : i > j;
    };
    sort(sa.begin(), sa.end(), cmp);
    for (int i = 0; i + 1 < n; ++i) t[i + 1] = t[i] + cmp(sa[i], sa[i + 1]);
    for (int i = 0; i < n; ++i) ra[sa[i]] = t[i];
  }
  return {sa, ra};
}

// O(N) -- CF: 1e6->31ms,18MB;1e7->296ms;158MB;3e7->856ms,471MB
bool is_lms(const string &t, int i) {
  return i > 0 && t[i - 1] == 'L' && t[i] == 'S';
}

template<typename T>
vector<int> induced_sort(const T &s, const string &t, const vector<int> &lmss, int sigma = 256) {
  vector<int> sa(s.size(), -1);

  vector<int> bin(sigma + 1);
  for (auto it = s.begin(); it != s.end(); ++it) {
    ++bin[*it + 1];
  }

  int sum = 0;
  for (int i = 0; i < bin.size(); ++i) {
    sum += bin[i];
    bin[i] = sum;
  }

  vector<int> cnt(sigma);
  for (auto it = lmss.rbegin(); it != lmss.rend(); ++it) {
    int ch = s[*it];
    sa[bin[ch + 1] - 1 - cnt[ch]] = *it;
    ++cnt[ch];
  }

  cnt = vector<int>(sigma);
  for (auto it = sa.begin(); it != sa.end(); ++it) {
    if (*it <= 0 || t[*it - 1] == 'S') continue;
    int ch = s[*it - 1];
    sa[bin[ch] + cnt[ch]] = *it - 1;
    ++cnt[ch];
  }

  cnt = vector<int>(sigma);
  for (auto it = sa.rbegin(); it != sa.rend(); ++it) {
    if (*it <= 0 || t[*it - 1] == 'L') continue;
    int ch = s[*it - 1];
    sa[bin[ch + 1] - 1 - cnt[ch]] = *it - 1;
    ++cnt[ch];
  }

  return sa;
}

template<typename T>
vector<int> sa_is(const T &s, int sigma = 256) {
  string t(s.size(), 0);
  t[s.size() - 1] = 'S';
  for (int i = int(s.size()) - 2; i >= 0; --i) {
    if (s[i] < s[i + 1]) t[i] = 'S';
    else if (s[i] > s[i + 1]) t[i] = 'L';
    else t[i] = t[i + 1];
  }

  vector<int> lmss;
  for (int i = 0; i < s.size(); ++i) {
    if (is_lms(t, i)) {
      lmss.emplace_back(i);
    }
  }

  vector<int> sa = induced_sort(s, t, lmss, sigma);
  vector<int> sa_lms;
  for (int i = 0; i < sa.size(); ++i) {
    if (is_lms(t, sa[i])) {
      sa_lms.emplace_back(sa[i]);
    }
  }

  int lmp_ctr = 0;
  vector<int> lmp(s.size(), -1);
  lmp[sa_lms[0]] = lmp_ctr;
  for (int i = 0; i + 1 < sa_lms.size(); ++i) {
    int diff = 0;
    for (int d = 0; d < sa.size(); ++d) {
      if (s[sa_lms[i] + d] != s[sa_lms[i + 1] + d] ||
          is_lms(t, sa_lms[i] + d) != is_lms(t, sa_lms[i + 1] + d)) {
        diff = 1; // something different in range of lms
        break;
      } else if (d > 0 && is_lms(t, sa_lms[i] + d) && is_lms(t, sa_lms[i + 1] + d)) {
        break; // exactly the same
      }
    }
    if (diff) ++lmp_ctr;
    lmp[sa_lms[i + 1]] = lmp_ctr;
  }

  vector<int> lmp_compact;
  for (int i = 0; i < lmp.size(); ++i) {
    if (~lmp[i]) {
      lmp_compact.emplace_back(lmp[i]);
    }
  }

  if (lmp_ctr + 1 < lmp_compact.size()) {
    sa_lms = sa_is(lmp_compact, lmp_ctr + 1);
  } else {
    for (int i = 0; i < lmp_compact.size(); ++i) {
      sa_lms[lmp_compact[i]] = i;
    }
  }

  vector<int> seed;
  for (int i = 0; i < sa_lms.size(); ++i) {
    seed.emplace_back(lmss[sa_lms[i]]);
  }

  return induced_sort(s, t, seed, sigma);
} // s must end in char(0)

// O(N) lcp, note that s must end in '\0'
vector<int> build_lcp(string &s, vector<int> &sa, vector<int> &ra) {
  int n = s.size();
  vector<int> lcp(n);
  for (int i = 0, h = 0; i < n; ++i) {
    if (ra[i] == 0) continue;
    if (h > 0) --h;
    for (int j = sa[ra[i] - 1]; max(j, i) + h < n; ++h) {
      if (s[j + h] != s[i + h]) break;
    }
    lcp[ra[i] - 1] = h;
  }
  return lcp; // lcp[i] := LCP(s[sa[i]], s[sa[i + 1]])
}

// O(N) build segment tree for lcp
vector<int> build_lcp_rmq(const vector<int> &lcp) {
  vector<int> sgt(lcp.size() << 2);
  function<void(int, int, int)> build = [&](int t, int lb, int rb) {
    if (rb - lb == 1) return sgt[t] = lcp[lb], void();
    int mb = lb + rb >> 1;
    build(t << 1, lb, mb);
    build(t << 1 | 1, mb, rb);
    sgt[t] = min(sgt[t << 1], sgt[t << 1 | 1]);
  };
  build(1, 0, lcp.size());
  return sgt;
}

// O(|P| + lg |T|) pattern searching, returns last index in sa
int match(const string &p, const string &s, const vector<int> &sa, const vector<int> &rmq) { // rmq is segtree on lcp
  int t = 1, lb = 0, rb = s.size(); // answer in [lb, rb)
  int lcplp = 0; // lcp(char(0), p) = 0
  while (rb - lb > 1) {
    int mb = lb + rb >> 1;
    int lcplm = rmq[t << 1];
    if (lcplp < lcplm) t = t << 1 | 1, lb = mb;
    else if (lcplp > lcplm) t = t << 1, rb = mb;
    else {
      int lcpmp = lcplp;
      while (lcpmp < p.size() && p[lcpmp] == s[sa[mb] + lcpmp]) ++lcpmp;
      if (lcpmp == p.size() || p[lcpmp] > s[sa[mb] + lcpmp]) t = t << 1 | 1, lb = mb, lcplp = lcpmp;
      else t = t << 1, rb = mb;
    }
  }
  if (lcplp < p.size()) return -1;
  return sa[lb];
}

int LCA(int i, int j, const vector<int> &ra, const vector<int> &lcp_seg) {
  // lca of ith and jth suffix
  if (ra[i] > ra[j]) swap(i, j);
  function<int(int, int, int, int, int)> query = [&](int L, int R, int l, int r, int v) {
    if (L <= l and r <= R) return lcp_seg[v];
    int m = l + r >> 1, ans = 1e9;
    if (L < m) ans = min(ans, query(L, R, l, m, v << 1));
    if (m < R) ans = min(ans, query(L, R, m, r, v << 1|1));
    return ans;
  };
  return query(ra[i], ra[j], 0, ra.size(), 1);
}
vector<vector<int>> build_lcp_sparse_table(const vector<int> &lcp) {
  int n = lcp.size(), lg = 31 - __builtin_clz(n);
  vector<vector<int>> st(lg + 1, vector<int>(n));
  for (int i = 0; i < n; ++i) st[0][i] = lcp[i];
  for (int j = 1; (1<<j) <= n; ++j)
    for (int i = 0; i + (1<<j) <= n; ++i)
      st[j][i] = min(st[j - 1][i], st[j - 1][i + (1<<(j - 1))]);
  return st;
}
int sparse_rmq(int i, int j, const vector<int> &ra, const vector<vector<int>> &st) {
  int n = st[0].size();
  if (ra[i] > ra[j]) swap(i, j);
  int k = 31 - __builtin_clz(ra[j] - ra[i]);
  return min(st[k][ra[i]], st[k][ra[j] - (1<<k)]);
}// sparse_rmq(sa[i], sa[j], ra, st) is the lcp of sa(i), sa(j)
