// 最長増加部分列の長さ
// 蟻本 p.64

int dp[MAX_N];
int lis(int *A, int N) {
  fill(dp, dp + N, INF);
  REP(i, N) {
    int pos = lower_bound(dp, dp + N, A[i]) - dp;
    dp[pos] = A[i];
  }
  return lower_bound(dp, dp + n, INF) - dp;
}
