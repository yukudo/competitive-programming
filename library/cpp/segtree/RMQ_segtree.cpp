// [               1              ]
// [       2      ][       3      ]
// [   4  ][   5  ][   6  ][   7  ]
// [ 8][ 9][10][11][12][13][14][15]
// - root が 1 の完全二分木
// - ある頂点の番号を k とすると左の子は 2*k, 右の子は 2*k+1, 親は k/2 
// - 最下段の左端の番号 == 最下段の長さ == n
// - 最大値を返すように変更するには、
//   - min を max に変える
//   - 初期値を INF から -INF に変える
struct RMQ {
  typedef int Val;
  int n;
  vector<Val> vs;
  void clear(int N) {
    for (n = 1; n < N; n <<= 1);
    vs.assign(n * 2, INF);
  }
  Val get(int pos) {
    return vs[n+pos];
  }
  void update(int pos, Val val) {
    vs[n+pos] = val;
    for (int k = (n+pos)/2; k > 0; k >>= 1)
      vs[k] = min(vs[2*k], vs[2*k+1]);
  }
  // [l, r) の最小値を返す
  Val query(int l, int r) {
    return query(0, n, 1, l, r);
  }
  Val query(int nl, int nr, int k, int l, int r) {
    if (r <= nl || nr <= l) return INF;
    if (l <= nl && nr <= r) return vs[k];
    Val x = query(nl, (nl+nr)/2, 2*k  , l, r);
    Val y = query((nl+nr)/2, nr, 2*k+1, l, r);
    return min(x, y);
  }
};
