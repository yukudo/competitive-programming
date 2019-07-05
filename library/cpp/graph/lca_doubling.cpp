const int MAX_N = 112345;
vector<int> g[MAX_N];

struct LCA {

  int log2(int b) {return 31 - __builtin_clz(b);}

  int parent[20][MAX_N]; // [k][i] := i からちょうど 2^k 回親方向へ進んだ頂点番号。無いなら -1
  int depth[MAX_N];
  int N;

  LCA(){}

  void build(int N, int root) {
    CLR(parent, -1);
    this->N = N;
    int K = log2(N) + 1;
    dfs(root, -1, 0);
    for (int k = 0; k < K; k++) {
      for (int i = 0; i < N; i++) {
        parent[k+1][i] = parent[k][i] >= 0 ? parent[k][parent[k][i]] : -1;
      }
    }
  }
  void dfs(int u, int p, int d) {
    parent[0][u] = p;
    depth[u] = d;
    for (int v : g[u]) if (v != p) {
      dfs(v, u, d+1);
    }
  }
  int get(int u, int v) {
    if (depth[u] > depth[v]) swap(u, v);
    int K = log2(N) + 1;
    for (int k = 0; k < K; k++) {
      if ((depth[v] - depth[u]) >> k & 1) {
        v = parent[k][v];
      }
    }
    if (u == v) return u;
    for (int k = K-1; k >= 0; k--) {
      if (parent[k][u] != parent[k][v]) {
        u = parent[k][u];
        v = parent[k][v];
      }
    }
    return parent[0][u];
  }
};

LCA lca;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C
int main2() {

  REP(i, MAX_N) g[i].clear();

  int N = nextInt();
  REP(i, N) {
    int K = nextInt();
    REP(_, K) {
      int j = nextInt();
      g[i].push_back(j);
      g[j].push_back(i);
    }
  }
  lca.build(N, 0);
  int Q = nextInt();
  REP(_, Q) {
    int u = nextInt();
    int v = nextInt();
    int ans = lca.get(u, v);
    printf("%d\n", ans);
  }
  return 0;
}
