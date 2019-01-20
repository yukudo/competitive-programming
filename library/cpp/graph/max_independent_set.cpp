// graph はビットセットの隣接行列。graph[i][i] は 0 にしておくこと。
// 頂点 v を使う/使わないで分岐。使う場合は隣接する頂点を消す。次数が 1 以下の頂点は必ず使う。
// n <= 40 ぐらいまで大丈夫。
// O(1.466^n)
// https://www.slideshare.net/wata_orz/ss-12131479/27
int max_independent_set(const vector<ll> graph, int v = 0, ll done = 0) {
  if ((int) graph.size() == v) { return 0; }
  if (done >> v & 1) return max_independent_set(graph, v+1, done); // v を使わない
  int deg = __builtin_popcount(graph[v] & ~done);
  int res = 1 + max_independent_set(graph, v+1, done | (1LL << v) | graph[v]); // v を使う
  if (deg > 1) {
    res = max(res, max_independent_set(graph, v+1, done | (1LL << v))); // vを使わない
  }
  return res;
}

int main() {
  int N, M; cin >> N >> M;
  bool adj[N][N] = {0};
  REP(i, M) {
    int a, b; cin >> a >> b;
    adj[a][b] = adj[b][a] = true;
  }
  vector<ll> g(N);
  REP(i, N) REP(j, N) if (i != j && adj[i][j]) g[i] |= 1LL << j;
  int ans = max_independent_set(g);
  cout << ans << endl;
}
