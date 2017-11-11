// 点を更新（ただし小さくすることはできない）、範囲 max
// - 内部的には 1-based であるが、利用するときには 0-based な実装
// - 範囲がどちら向きかはコメントアウトしてるところを切り替える
// - max を min に変えると BITMIN になる
// - 初期値は 0/INF/-INF を問題によって決める
struct BITMAX {
  int n;
  int vs[MAX_N + 1];
  BITMAX() {
    this->n = MAX_N;
    clear();
  }
  void clear() {
    REP(i, n+1) vs[i] = 0; // default value
  }
  void update(int idx, int val) {
    for (int x = idx + 1; x > 0; x -= x & -x) vs[x] = max(vs[x], val); // [0, idx] の範囲の最大値を val で更新しようと試みる
    // for (int x = idx + 1; x <= n; x += x & -x) vs[x] = max(vs[x], val); // [idx, ∞] の範囲の最大値を val で更新しようと試みる
  }
  int get(int idx) {
    int val = 0; // default value
    for (int x = idx + 1; x <= n; x += x & -x)  val = max(val, vs[x]); // [0, idx] の範囲の最大値を取得
    // for (int x = idx + 1; x > 0; x -= x & -x) val = max(val, vs[x]); // [idx, ∞] の範囲の最大値を取得
    return val;
  }
};
