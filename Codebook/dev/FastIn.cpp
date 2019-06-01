template<size_t BUF_LEN> // 1 << 10 works pretty good
struct FastIn {
  char nxt_ch() {
    static char buf[BUF_LEN], *pst = buf + BUF_LEN, *ped = buf + BUF_LEN;
    if (pst == ped) {
      pst = buf;
      ped = buf + fread(buf, 1, BUF_LEN, stdin);
      if (pst == ped) return 0;
    }
    return *pst++;
  }
  int read_int() { // make sure you are going to read an int
    char c;
    while ((c = nxt_ch()) < 48 && c != 45);
    auto plus = c == 45 ? [](int a, int b) { return a - b; } : [](int a, int b) { return a + b; };
    int x = 47 < c ? c - 48 : 0;
    for (; 47 < (c = nxt_ch()); x = plus(x * 10, c - 48));
    return x;
  }
};
