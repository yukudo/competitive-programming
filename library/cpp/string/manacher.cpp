// 文字列 S が与えられた時、各 i について
// 「文字 i を中心とする最長の回文の半径」
// を記録した配列 palin を O(|S|) で構築する。
// 半径というのは、(全長+1)/2です。
// http://snuke.hatenablog.com/entry/2014/12/02/235837

int palin[MAX_N];
void manacher(const string s) {
  int N = (int)s.size();
  int i = 0, j = 0;
  while (i < N) {
    while (i-j >= 0 && i+j < N && s[i-j] == s[i+j]) j++;
    palin[i] = j;
    int k = 1;
    while (i-k >= 0 && i+k < N && k + palin[i-k] < j) { palin[i+k] = palin[i-k]; k++; }
    i += k;
    j -= k;
  }
  
  cout << s << endl;
  REP(i, N) cout << palin[i]; cout << endl;
}
