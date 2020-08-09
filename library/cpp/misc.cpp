// ============================================================================

template<class T>
vector<pair<T, ll>> runLength(const vector<T>& xs) {
  vector<pair<T, ll>> res;
  for (auto x : xs) {
    if (res.empty() || res.back().first != x) {
      res.push_back({x, 1});
    } else {
      ++res.back().second;
    }
  }
  return res;
}

// ============================================================================
// 二次元累積和

const int MAX_N = 5000;

ll A[MAX_N][MAX_N];
ll acc[MAX_N + 1][MAX_N + 1];

void build(int N) {
  REP(i, N) REP(j, N) {
    acc[i+1][j+1] = acc[i+1][j] + acc[i][j+1] - acc[i][j] + A[i][j];
  }
}

// for (int r = r0; r < r1; r++) for (int c = c0; c < c1; c++) res += A[r][c];
ll get(int r0, int c0, int r1, int c1) {
  return acc[r1][c1] - acc[r0][c1] - acc[r1][c0] + acc[r0][c0];
}

// ============================================================================

