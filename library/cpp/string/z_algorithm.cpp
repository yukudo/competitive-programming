
// 入力の長さを n として、長さ n の配列を返す。
// i 番目の要素は s[0..n)とs[i..n)のLCP(Longest Common Prefix)の長さ。
template<class T> vector<int> z_algorithm(vector<T> s) {
  int N = s.size();
  vector<int> z(N);
  z[0] = N;
  int from = -1, last = -1;
  for (int i = 1; i < N; i++) {
    int& len = z[i];
    if (from != -1) {
      len = max(0, min(z[i - from], last - i));
    }
    while (i + len < N && s[len] == s[i + len]) len++;
    if (last < i + len) {
      from = i;
      last = i + len;
    }
  }
  return z;
}

vector<int> z_algorithm(string s) {
  int N = s.size();
  vector<int> s2(N);
  REP(i, N) s2[i] = s[i];
  return z_algorithm(s2);
}
