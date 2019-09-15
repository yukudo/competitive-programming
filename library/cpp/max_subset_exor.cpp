/**
 * 整数の集合Aと整数Xが与えられる。
 * Aの部分集合Sに対して関数f(S)をSの全要素をexorした値と定義する。
 * X ^ f(S) の最大値を求める。
 */
ll maxSubsetExor(vector<ll> A, ll X) {

  const int N = A.size();
  const int M = 62;

  auto at = [&](const ll Ai, const int j) -> int {
    return (Ai >> (M-j-1) & 1);
  };

  int s = 0;
  REP(j, M) {
    int p = -1;
    for (int i = s; i < N; i++) if (at(A[i], j)) { p = i; break; }
    if (p != -1) {
      swap(A[s], A[p]);
      for (int i = s+1; i < N; i++) if (at(A[i], j)) A[i] ^= A[s];
      s++;
    }
  }

  ll ans = X;
  s = 0;
  REP(j, M) {
    if (at(ans, j) == 0 && at(A[s], j)) ans ^= A[s];
    if (at(A[s], j)) s++;
  }

  return ans;
}
