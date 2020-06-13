// 連結で単純な無向グラフの、極小なサイクルをひとつ見つける。最小ではない。
// dfsしてサイクルをひとつ見つける。
// そのサイクルを横切る辺があれば、それを使ってより小さいサイクルを作れる。見つからなくなるまで繰り返し。
// 1回でサイクルのサイズは1/2以下になるのでO(logN)回で繰り返しは終了する。

const int MAX_N = 212345;
vector<int> g[MAX_N];

int vis[MAX_N];
vector<int> history;
bool inHist[MAX_N];
vector<int> cycle;
void dfs(int cur, int prev, int depth) {
  if (inHist[cur]) {
    for (;;) {
      cycle.push_back(history.back());
      if (history.back() == cur) break;
      history.pop_back();
    }
    throw 1;
  }
  if (vis[cur]) return;
  vis[cur] = depth;
  history.push_back(cur);
  inHist[cur] = true;
  for (int nxt : g[cur]) if (nxt != prev) {
    dfs(nxt, cur, depth + 1);
  }
  history.pop_back();
  inHist[cur] = false;
}

vector<int> minimal_cycle(const int N) {

  CLR(vis, 0);
  CLR(inHist, 0);
  history.clear();
  cycle.clear();
  try { dfs(0, -1, 1); } catch (int e) {};
  if (cycle.size() == 0) return {};

  for (;;) {
    vector<int> inCycle(N, -1);
    const int L = cycle.size();
    REP(i, L) inCycle[ cycle[i] ] = i;
    int min_len = L, from = 0, to = L-1;
    REP(i, L) {
      int cur = cycle[i];
      for (int nxt : g[cur]) {
        int j = inCycle[nxt];
        if (j == -1 || abs(i - j) == 1 || abs(i - j) == L-1) continue;
        int len = i < j ? L - (j - i) : i - j + 1;
        if (min_len > len) {
          min_len = len;
          if (i < j) { from = j, to = i; } else { from = i, to = j; }
        }
      }
    }
    if (min_len == L) break;
    vector<int> n_cycle;
    for (int i = from; i != to; i = (i + 1) % L) n_cycle.push_back(cycle[i]);
    n_cycle.push_back(cycle[to]);
    swap(cycle, n_cycle);
  }
  return cycle;
}
