// 点を更新（ただし小さくすることはできない）、範囲 max 
// 内部的には 1-based であるが、利用するときには 0-based な実装
struct BITMAX {
  int n;
  int vs[MAX_N];
  BITMAX(int n) : n(n) {
    clear();
  }
  void clear() {
    memset(vs, 0, sizeof(vs));
  }
  // 点 idx をval で更新を試みる
  // 別の見方では範囲 [idx, ∞] を val で更新を試みる
  void update(int idx, int val) {
    for (int x = idx + 1; x <= n; x += x & -x) vs[x] = max(vs[x], val);
  }
  // [0, idx] での最大値を返す
  int get(int idx) {
    int ma = 0;
    for (int x = idx + 1; x > 0; x -= x & -x) ma = max(ma, vs[x]);
    return ma;
  }
  
};
