/**
 * Sparse Table による RMQ の実装。
 * 区間のmin
 * 構築O(nlogn), クエリO(1)
 * 更新ができない。
 * SegmentTreeによる実装よりも定数倍がかなり高速。
 */
struct RMQStatic {
  int *a;
  int dp_min[20][MAX_N]; // [i][j] := answer index of start_pos == j, len == 2^i
  int dp_max[20][MAX_N];

  int log2(int b) {return 31 - __builtin_clz(b);}

  // O(NlogN)
  void build(int* a, int N) {
    this->a = a;
    int M = log2(N) + 1;
    REP(i, N) dp_min[0][i] = i;
    REP(i, N) dp_max[0][i] = i;
    for (int i = 1, len = 1; i < M; i++, len <<= 1) {
      for (int j = 0; j + len < N; j++) {
        {
          int s = dp_min[i - 1][j];
          int t = dp_min[i - 1][j + len];
          dp_min[i][j] = a[s] <= a[t] ? s : t;
        }
        {
          int s = dp_max[i - 1][j];
          int t = dp_max[i - 1][j + len];
          dp_max[i][j] = a[s] >= a[t] ? s : t;
        }
      }
    }
  }

  // O(1)
  // [from..to]の間で最小の値の添字を返す。複数ある場合は一番最初のを返す
  int query(int from, int to, int type) {
    int k = log2(to - from + 1);
    if (type == 0) {
      int s = dp_min[k][from];
      int t = dp_min[k][to - (1 << k) + 1];
      return a[s] <= a[t] ? s : t;
    } else {
      int s = dp_max[k][from];
      int t = dp_max[k][to - (1 << k) + 1];
      return a[s] >= a[t] ? s : t;
    }
  }
};
