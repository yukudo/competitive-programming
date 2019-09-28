// いわゆる Starry Sky Tree
// その区間に一様に足されている値を持つ実装
//
// [               1              ]
// [       2      ][       3      ]
// [   4  ][   5  ][   6  ][   7  ]
// [ 8][ 9][10][11][12][13][14][15]
// - root が 1 の完全二分木
// - ある頂点の番号を k とすると左の子は 2*k, 右の子は 2*k+1, 親は k/2
// - 最下段の左端の番号 == 最下段の長さ == n
const ll INF = 1LL << 61;
struct RangeAddRangeMin {
  using Val = ll;
  int n;
  vector<Val> segMin;
  vector<Val> segAdd; // 区間に一様に足されている値

  void clear(int N) {
    for (n = 1; n < N; n <<= 1);
    segMin.assign(n * 2, 0);
    segAdd.assign(n * 2, 0);
    segAdd[1] = INF; // 初期値
  }

  // [l, r) の最小値
  Val getMin(int l, int r) {
    if (r - l <= 0) return INF;
    return getMin(0, n, 1, l, r);
  }
  Val getMin(int nl, int nr, int k, int l, int r) {
    if (r <= nl || nr <= l) return INF;
    if (l <= nl && nr <= r) return segMin[k] + segAdd[k];
    Val x = getMin(nl, (nl+nr)/2, 2*k  , l, r);
    Val y = getMin((nl+nr)/2, nr, 2*k+1, l, r);
    return min(x, y) + segAdd[k];
  }

  // [l, r) の全てに val を加算
  void addRange(int l, int r, Val val) {
    addRange(0, n, 1, l, r, val);
  }
  void addRange(int nl, int nr, int k, int l, int r, Val val) {
    if (r <= nl || nr <= l) return;
    if (l <= nl && nr <= r) { segAdd[k] += val; return; }
    addRange(nl, (nl+nr)/2, 2*k  , l, r, val);
    addRange((nl+nr)/2, nr, 2*k+1, l, r, val);
    segMin[k] = min(segMin[2*k]+segAdd[2*k], segMin[2*k+1]+segAdd[2*k+1]);
  }

  // pos の値を強制的に val にする
  void update(int pos, Val val) {
    Val now = getMin(pos, pos + 1);
    addRange(pos, pos+1, val - now);
  }
};
