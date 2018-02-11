// N個の品物がある。
// 品物 i は重さ w[i], 価値 v[i] で、 u[i] 個ある。
// 重さの総和が W を超えないように価値の総和の最大値を求めなさい。
// 蟻本 p.302
// 愚直解
// dp[i][j] := 最初のi個の品物で重さjとなるときの価値の最大値
// dp[i][j] = max( dp[i-1][j], 
//                 dp[i-1][j-  w[i]] +   v[i],
//                 ...,
//                 dp[i-1][j-k*w[i]] + k*v[i])
// O(NW max(u))
// 
// 高速解
// MOD w[i] で独立に考える。
// a[j] = dp[i][j*w[i]]
// b[j] = a[j] - j*v[i]
// と置いて式変形すると
// dp[i][(k+j)w[i]] = (j+k)v[j] + max(b[j], b[j+1], ..., b[j+k])
// スライド最小値の技法が使えて O(NW) で解ける

const int MAX_N = 105;
const int MAX_W = 10005;
int N, W;
int w[MAX_N];
int v[MAX_N];
int u[MAX_N];

ll dp[MAX_N][MAX_W];

ll naive() {
  REP(i, N) REP(j, W+1) {
    ll res = 0;
    for (int k = 0; k <= u[i] && j-k*w[i] >= 0; k++) {
      chmax(res, dp[i][j-k*w[i]] + k*v[i]);
    }
    dp[i+1][j] = res;
  }
  return dp[N][W];
}

// O(NW)
// なお配列 dp は使いまわせるので実は dp[MAX_W] で良い。
pair<int,ll> deq[MAX_W]; // <index, value>
ll fast() {
  REP(i, N) REP(a, w[i]) {
    int s = 0, t = 0;
    for (int j = 0; j*w[i] + a <= W; j++) {
      ll val = dp[i][j*w[i] + a] - j*v[i];
      while (s < t && deq[t-1].second <= val) t--;
      deq[t++] = {j, val};
      dp[i+1][j*w[i] + a] = deq[s].second + j*v[i];
      if (deq[s].first == j - u[i]) s++;
    }
  }
  return dp[N][W];
}
