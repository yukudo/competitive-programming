// 重みなし二部グラフマッチング
// Deprecated. かわりに bool の隣接行列での dinic を使えばいいと思う

const int MAX_N = 1000;
const int MAX_M = 1000;

int N,M;
bool edge[MAX_N][MAX_M];
bool visited[MAX_N];
int from[MAX_M];

bool add(int p) {
  if (visited[p]) return false;
  visited[p] = true;
  REP(i, M) if (edge[p][i]) {
    if (from[i] < 0 || add(from[i])) {
      from[i] = p;
      return true;
    }
  }
  return false;
}

int matching() {
  CLR(from, -1);
  int res = 0;
  REP(i, N) {
    CLR(visited, 0);
    if (add(i))
      ++res;
  }
  return res;
}
