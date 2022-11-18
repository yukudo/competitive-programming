/**
 * 密グラフを bool の隣接行列で持つ dinic
 * 二部マッチングは、グラフが疎なら ACL を、密ならこれを使う
 */

const int MAX_V = 20010;
vector< vector<bool> > dinic_g; // bool の隣接行列
int level[MAX_V];
int done[MAX_V];

void reset_graph(int n) { dinic_g = vector< vector<bool> >(n, vector<bool>(n)); }
void addedge(int from, int to) {
  dinic_g[from][to] = true;
}

int dinic_dfs(int v, int t) {
  if (v == t) return 1;
  for ( ; done[v] < (int)dinic_g.size(); done[v]++) {
    int dst = done[v];
    if (!dinic_g[v][dst] || level[v] >= level[dst]) continue;
    if (dinic_dfs(dst, t)) {
      dinic_g[v][dst] = false;
      dinic_g[dst][v] = true;
      return 1;
    }
  }
  return 0;
}

bool dinic_bfs(int s, int t) {
  memset(level, -1, sizeof(level));
  queue<int> q; q.push(s); level[s] = 0;
  while (!q.empty()) {
    int here = q.front(); q.pop();
    REP(dst, dinic_g.size()) if (dinic_g[here][dst] && level[dst] == -1) {
      level[dst] = level[here] + 1;
      q.push(dst);
    }
  }
  return level[t] >= 0;
}

int dinic(int s, int t) {
  int res = 0;
  while (dinic_bfs(s, t)) {
    memset(done, 0, sizeof(done));
    for (int f; (f = dinic_dfs(s, t)) > 0; ) res += f;
  }
  return res;
}
