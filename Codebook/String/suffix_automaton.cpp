template<typename T>
struct SuffixAutomaton {
  vector<map<int, int>> edges;// edges[i]  : the labeled edges from node i
  vector<int> link;           // link[i]   : the parent of i
  vector<int> length;         // length[i] : the length of the longest string in the ith class
  int last;                   // the index of the equivalence class of the whole string
  vector<bool> is_terminal;   // is_terminal[i] : some suffix ends in node i (unnecessary)
  vector<int> occ;            // occ[i] : number of matches of maximum string of node i (unnecessary)
  SuffixAutomaton(const T &s) : edges({map<int, int>()}), link({-1}), length({0}), last(0), occ({0}) {
    for (int i = 0; i < s.size(); ++i) {
      edges.push_back(map<int, int>());
      length.push_back(i + 1);
      link.push_back(0);
      occ.push_back(1);
      int r = edges.size() - 1;
      int p = last; // add edges to r and find p with link to q
      while (p >= 0 && edges[p].find(s[i]) == edges[p].end()) {
        edges[p][s[i]] = r;
        p = link[p];
      }
      if (~p) {
        int q = edges[p][s[i]];
        if (length[p] + 1 == length[q]) { // no need to split q
          link[r] = q;
        } else { // split q, add qq
          edges.push_back(edges[q]);  // copy edges of q
          length.push_back(length[p] + 1);
          link.push_back(link[q]);  // copy parent of q
          occ.push_back(0);
          int qq = edges.size() - 1; // qq is new parent of q and r
          link[q] = qq;
          link[r] = qq;
          while (p >= 0 && edges[p][s[i]] == q) { // what points to q points to qq
            edges[p][s[i]] = qq;
            p = link[p];
          }
        }
      }
      last = r;
    } // below unnecessary
    is_terminal = vector<bool>(edges.size());
    for (int p = last; p > 0; p = link[p]) is_terminal[p] = 1; // is_terminal calculated
    vector<int> cnt(link.size()), states(link.size()); // sorted states by length
    for (int i = 0; i < link.size(); ++i) ++cnt[length[i]];
    for (int i = 0; i < s.size(); ++i) cnt[i + 1] += cnt[i];
    for (int i = link.size() - 1; i >= 0; --i) states[--cnt[length[i]]] = i;
    for (int i = link.size() - 1; i >= 1; --i) occ[link[states[i]]] += occ[states[i]]; // occ calculated
  }
};
