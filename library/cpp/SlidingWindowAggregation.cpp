//
// deque の4操作に加えて prod_all() が行えるデータ構造。特殊ケースとして slide_min を作れる。
// 
const ll MOD = 998244353;
struct F { int a, b; };

F op(F f1, F f2) { 
  return (F){ 
    (int)((ll)f2.a * f1.a % MOD),
    (int)(((ll)f2.a * f1.b + f2.b) % MOD),
  };
}
F e() { return (F){ 1, 0 }; }

template <class S, auto op, auto e>
struct SlidingWindowAggregation {

  struct FoldableStack {
    vector<S> vals, prods;
    bool empty() const { return vals.empty(); }
    void push_r(S val) {
      vals.push_back(val);
      prods.push_back(prods.empty() ? val : op(prods.back(), val));
    }
    void push_l(S val) {
      vals.push_back(val);
      prods.push_back(prods.empty() ? val : op(val, prods.back()));
    }
    void pop() { if (!vals.empty()) { vals.pop_back(); prods.pop_back(); } }
    S all_prod() const { return prods.empty() ? e() : prods.back(); }
    S top() const { return vals.empty() ? e() : vals.back(); }
    S bottom() const { return vals.empty() ? e() : vals.front(); }
  };

  FoldableStack frontStack, backStack;

  //              front       back
  // push_front → --------+------- ← push_back
  //                1 2 3 | 4 5 
  // pop_front ←  --------+-------  → pop_back

  bool empty() const { return frontStack.empty() && backStack.empty(); }
  S front() const { 
    if (!frontStack.empty()) return frontStack.top();
    if (!backStack.empty()) return backStack.bottom();
    return e();
  }
  S back() const {
    if (!backStack.empty()) return backStack.top();
    if (!frontStack.empty()) return frontStack.bottom();
    return e();
  }
  void push_back(S val) { backStack.push_r(val); }
  void push_front(S val) { frontStack.push_l(val); }
  void pop_back() {
    if (empty()) return;
    if (!backStack.empty()) { backStack.pop(); return; }
    vector<S> tmp;
    while (!frontStack.empty()) {
      tmp.push_back(frontStack.top());
      frontStack.pop();
    }
    int n = tmp.size();
    for (int i = n/2 - 1; i >= 0; i--) frontStack.push_l(tmp[i]);
    for (int i = n/2; i + 1 < n; i++) backStack.push_r(tmp[i]);
  }
  void pop_front() {
    if (empty()) return;
    if (!frontStack.empty()) { frontStack.pop(); return; }
    vector<S> tmp;
    while (!backStack.empty()) {
      tmp.push_back(backStack.top());
      backStack.pop();
    }
    int n = tmp.size();
    for (int i = n/2 - 1; i >= 0; i--) backStack.push_r(tmp[i]);
    for (int i = n/2; i + 1 < n; i++) frontStack.push_l(tmp[i]);
  }
  // 現在入っている要素すべての op() を計算します。空のときは e() を返します。
  S all_prod() const {
    return op(frontStack.all_prod(), backStack.all_prod());
  }
};

int main2() {
  
  // https://judge.yosupo.jp/submission/169790

  SlidingWindowAggregation<F, op, e> deq;

  int Q = nextLong();
  while (Q--) {
    int t = nextLong();
    if (t == 0) {
      int a = nextLong();
      int b = nextLong();
      deq.push_back(F{a, b});
    }
    if (t == 1) {
      deq.pop_front();
    }
    if (t == 2) {
      int x = nextLong();
      F f = deq.all_prod();
      int ans = ((ll)f.a * x + f.b) % MOD;
      cout << ans << '\n';
    }
  }
  return 0;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

#ifdef LOCAL
  for (;!cin.eof();cin>>ws)
#endif
    main2();
  return 0;
}
