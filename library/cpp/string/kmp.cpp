// 
// 長さ N の文字列 S が与えられる。 以下のような配列 int border[N] を O(N) で求める。 
// border[i] := S の先頭 i 文字を考えたときに、そのprefixとsuffixが一致するような部分長さ L(0 <= L < i) のうち最長のもの
// (L < i であることに注意。L = iのような自明なprefix/suffixは考えない)
//
// http://snuke.hatenablog.com/entry/2014/12/01/235807
// http://snuke.hatenablog.com/entry/2017/07/18/101026
// http://potetisensei.hatenablog.com/entry/2017/07/10/174908

int border[MAX_N];
int kmpnxt[MAX_N];
void KMP(const string& S) {
  int N = (int)S.size();
  border[0] = kmpnxt[0] = -1;
  for (int i = 0, j = -1; i < N; i++) { 
    while (j >= 0 && S[i] != S[j]) j = kmpnxt[j];
    j++;
    border[i+1] = j;
    kmpnxt[i+1] = (S[i+1] == S[j]) ? kmpnxt[j] : j;
  }
  cout << "S     :"; pv(ALL(S));
  cout << "border:"; pv(border, border+N+1);
  cout << "kmpnxt:"; pv(kmpnxt, kmpnxt+N+1);
}
