//
// deque の4操作に加えて prod_all() が行えるデータ構造。特殊ケースとして slide_min を作れる。
// 

int op(int a, int b) { return min(a, b); }
int e() { return (int)(1e9); }

template <class S, auto op, auto e>
struct SlidingWindowAggregation {

  struct FoldableStack {
    vector<S> vals, prods;
    bool empty() const { return vals.empty(); }
    void push(S val) {
      vals.push_back(val);
      prods.push_back(prods.empty() ? val : op(prods.back(), val));
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
  void push_back(S val) { backStack.push(val); }
  void push_front(S val) { frontStack.push(val); }
  void pop_back() {
    if (empty()) return;
    if (!backStack.empty()) { backStack.pop(); return; }
    vector<S> tmp;
    while (!frontStack.empty()) {
      tmp.push_back(frontStack.top());
      frontStack.pop();
    }
    int n = tmp.size();
    for (int i = n/2 - 1; i >= 0; i--) frontStack.push(tmp[i]);
    for (int i = n/2; i < n; i++) backStack.push(tmp[i]);
    backStack.pop();
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
    for (int i = n/2 - 1; i >= 0; i--) backStack.push(tmp[i]);
    for (int i = n/2; i < n; i++) frontStack.push(tmp[i]);
    frontStack.pop();
  }
  // 現在入っている要素すべての op() を計算します。空のときは e() を返します。
  S all_prod() const {
    return op(frontStack.all_prod(), backStack.all_prod());
  }
};
