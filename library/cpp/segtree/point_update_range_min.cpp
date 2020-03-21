// [               1              ]
// [       2      ][       3      ]
// [   4  ][   5  ][   6  ][   7  ]
// [ 8][ 9][10][11][12][13][14][15]
// - root が 1 の完全二分木
// - ある頂点の番号を k とすると左の子は 2*k, 右の子は 2*k+1, 親は k/2
// - 最下段の左端の番号 == 最下段の長さ == n
struct PointUpdateRangeMax {
  using Val = ll;
  int n;
  vector<Val> seg;
  void clear(int N) {
    for (n = 1; n < N; n <<= 1);
    seg.assign(n * 2, -INF); // 初期値
  }
  // [l, r)
  Val getMax(int l, int r) {
    if (r - l <= 0) return -INF;
    return getMax(0, n, 1, l, r);
  }
  Val getMax(int nl, int nr, int k, int l, int r) {
    if (r <= nl || nr <= l) return -INF;
    if (l <= nl && nr <= r) return seg[k];
    Val x = getMax(nl, (nl+nr)/2, 2*k  , l, r);
    Val y = getMax((nl+nr)/2, nr, 2*k+1, l, r);
    return max(x, y);
  }
  void update(int pos, ll val) {
    int k = n + pos;
    seg[k] = val;
    while (k/2 >= 1) {
      k /= 2;
      seg[k] = max(seg[2*k], seg[2*k+1]);
    }
  }
};
