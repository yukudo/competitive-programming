// 反転数
// a[i] > a[j] かつ  i < j である組 (i,j) の個数
// バブルソートの交換回数でもある
// 蟻本 p.162

ll inversion_number(int *A, int N) {
  ll ans = 0;
  // normalize(A); // 座標圧縮
  BIT bit(N + 5);
  REP(i, N) {
    ans += bit.range(N - A[i]);
    bit.add(N - A[i], 1);
  }
  return ans;
}
