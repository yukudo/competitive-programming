// 初期状態は全て 0 
// - 区間 [l, r) を値 v で更新（ここで v は過去のどの値よりも大きい場合しか確かめていない）
// - 範囲 [l, r) の最大値を取得
// 遅延評価セグツリーによる実装。
struct RangeUpdateRangeMax {
  typedef ll Val;
  int n;
  vector<Val> seg;
  vector<Val> lazy;
  const Val UNITY_LAZY = -1;
  void clear(int N) {
    for (n = 1; n < N; n <<= 1);
    seg.assign(n * 2, 0);
    lazy.assign(n * 2, UNITY_LAZY);
    seg[1] = 0; // 初期値
  }

  void eval_lazy(int nl, int nr, int k) {
    if (lazy[k] != UNITY_LAZY) {
      chmax(seg[k], lazy[k]);
      if (nr - nl >= 2) {
        chmax(lazy[2*k  ], lazy[k]);
        chmax(lazy[2*k+1], lazy[k]);
      }
      lazy[k] = UNITY_LAZY;
    }
  }
  // [l, r) の最大値
  Val getMax(int l, int r) {
    if (r - l <= 0) return 0;
    return getMax(0, n, 1, l, r);
  }
  Val getMax(int nl, int nr, int k, int l, int r) {
    eval_lazy(nl, nr, k);
    if (r <= nl || nr <= l) return 0;
    if (l <= nl && nr <= r) {
      return seg[k];
    }
    Val x = getMax(nl, (nl+nr)/2, 2*k  , l, r);
    Val y = getMax((nl+nr)/2, nr, 2*k+1, l, r);
    return max(x, y);
  }

  // [l, r) の全てを val で更新
  void updateRange(int l, int r, Val val) {
    updateRange(0, n, 1, l, r, val);
  }
  void updateRange(int nl, int nr, int k, int l, int r, Val val) {
    eval_lazy(nl, nr, k);
    if (r <= nl || nr <= l) return;
    if (l <= nl && nr <= r) { lazy[k] = val; eval_lazy(nl, nr, k); return; }
    updateRange(nl, (nl+nr)/2, 2*k  , l, r, val);
    updateRange((nl+nr)/2, nr, 2*k+1, l, r, val);
    seg[k] = max(seg[2*k], seg[2*k+1]);
  }
};
