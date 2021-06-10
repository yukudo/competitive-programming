
template<class T>
struct CumulativeSum {
  int R, C;
  vector<vector<T>> acc;

  CumulativeSum(int R, int C) {
    this->R = R;
    this->C = C;
    acc.assign(R+1, vector<T>(C+1));
  }

  // A[r][c] += v;
  void add(int r, int c, T v) {
    if (!(0 <= r && r < R && 0 <= c && c < C)) return;
    acc[r+1][c+1] += v;
  }

  void build() {
    REP(i, R) REP(j, C) {
      acc[i+1][j+1] += acc[i+1][j] + acc[i][j+1] - acc[i][j];
    }
  }

  // A[r][c];
  T val(int r, int c) const {
    return range(r, c, r+1, c+1);
  }

  // for (int r = r0; r < r1; r++) for (int c = c0; c < c1; c++) res += A[r][c];
  T range(int r0, int c0, int r1, int c1) const {
    return acc[r1][c1] - acc[r0][c1] - acc[r1][c0] + acc[r0][c0];
  }

};
