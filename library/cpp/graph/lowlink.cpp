const int MAX_N = 312345;
vector<int> g[MAX_N];

int ord[MAX_N]; // 訪れた順につける番号
int low[MAX_N]; // DFS 木の葉方向の辺を 0 回以上、後退辺を 1 回以下でたどり着ける ord の最小値
bool isArticulation[MAX_N];

void dfs(int u, int p, int &ordc) {
  low[u] = ord[u] = ordc++;
  int deg = 0;
  bool isa = false;
  for (int v : g[u]) if (v != p) {
    if (ord[v] == -1) { // まだ訪れてない
      deg++;
      dfs(v, u, ordc);
      low[u] = min(low[u], low[v]);
      if (ord[u] <= low[v]) isa = true;
    } else { // まだ (u,v) を使ってない
      // このとき (u,v) は後退辺
      low[u] = min(low[u], ord[v]);
    }
  }

  // 頂点 u が関節点 <=> u が DFS 木の根なら次数 > 1 かどうか、uがそれ以外なら ord[u] <= low[v] なる u の子 v が存在するかどうか
  isArticulation[u] = (p == -1 ? deg >= 2 : isa);
}
void lowlink(int N) {
  CLR(ord, -1);
  CLR(isArticulation, 0);
  int ordc = 0;
  REP(u, N) if (ord[u] == -1) {
    dfs(u, -1, ordc);
  }
}
// DFS 木の辺 e(u, v) が橋 <=> ord[u] < low[v]
bool isBridge(int u, int v) {
  if (ord[u] > ord[v]) swap(u, v);
  return ord[u] < low[v];
}


// 関節点 http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A
// 橋 http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B
int main2() {
  REP(i, MAX_N) g[i].clear();
  int N = nextInt();
  int M = nextInt();
  REP(i, M) {
    int a = nextInt();
    int b = nextInt();
    g[a].push_back(b);
    g[b].push_back(a);
  }

  lowlink(N);

  vector<pair<int,int>> bridges;
  REP(i, N) {
    for (int j : g[i]) if (i < j) {
      if (isBridge(i, j)) bridges.push_back({i, j});
    }
  }
  sort(ALL(bridges));
  for (auto b : bridges) printf("%d %d\n", b.first, b.second);

  return 0;
}
