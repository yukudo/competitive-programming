// 01ベクトルのランクを求める
int binary_matrix_rank(vector<ll> A) {
  const int N = A.size();
  const int M = 62;

  auto at = [](const ll Ai, int j) -> int {
    return Ai >> (M - 1 - j) & 1;
  };

  int s = 0;
  REP(j, M) {
    int p = -1;
    for (int i = s; i < N; i++) if (at(A[i], j)) { p = i; break; }
    if (p >= 0) {
      swap(A[s], A[p]);
      for (int i = s+1; i < N; i++) if (at(A[i], j)) A[i] ^= A[s];
      s++;
    }
  }
  return s;
}
