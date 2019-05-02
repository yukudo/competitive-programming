// 与えられた数列 A の連続する部分列の or すなわち
// 0 <= i <= j <= N-1 について A[i] or ... or A[j] を考える。
// i を固定して j を動かすとき、取りうる値は高々[要素のビット数]種類である。
// 理由は、立っているビットの数が変化するのがせいぜいビット数回なので。
// 各 i について、それぞれの値を取る最初の位置を求める。

const int MAX_N = 212345;
int N;
ll A[MAX_N];
int next1[MAX_N][64]; // next1[i][k] := k ビット目について位置 i より後ろで最も早く 1 が出てくる場所
vector<pair<ll,int>> B[MAX_N]; // B[i] := 区間[i, *]についてのorについて、値が変わる場所とその値

void build() {
  REP(k, 64) {
    int pos = N;
    for (int i = N-1; i >= 0; i--) {
      next1[i][k] = pos;
      if (A[i] >> k & 1) pos = i;
    }
  }
  REP(i, N) {
    auto &list = B[i];
    set<int> js({i});
    REP(k, 64) js.insert(next1[i][k]);
    ll val = 0;
    for (int j : js) if (j < N) {
      val |= A[j];
      if (list.empty() || list.back().first != val) list.push_back({val,j});
    }
  }
}
