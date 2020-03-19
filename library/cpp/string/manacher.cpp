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
    while (i-k >= 0 && k + palin[i-k] < j) { palin[i+k] = palin[i-k]; k++; }
    i += k;
    j -= k;
  }
  
  cout << s << endl;
  REP(i, N) cout << palin[i]; cout << endl;
}

// 偶数長の回文を検出するためには文字の間にダミーの文字を挟む。
// 全ての極大な回文を列挙する使用例。
void enumerate(const string s) {
  const int N = s.size();
  string SS;
  REP(i, N) {
    SS.push_back('.');
    SS.push_back(s[i]);
  }
  SS.push_back('.');
  manacher(SS);
  cout << s << endl;
  for (int x = 1; x < 2*N; x++) {
    int a = ((x - palin[x] + 1) + 1) / 2;
    int b = ((x + palin[x] - 1) + 1) / 2;
    cout << x << " " << s.substr(a, b - a) << endl;
  }
}
// enumerate("abaaababa");
// .a.b.a.a.a.b.a.b.a.
// 1214123832141614121
// abaaababa
// 1 a
// 2
// 3 aba
// 4
// 5 a
// 6 aa
// 7 abaaaba
// 8 aa
// 9 a
// 10
// 11 aba
// 12
// 13 ababa
// 14
// 15 aba
// 16
// 17 a
