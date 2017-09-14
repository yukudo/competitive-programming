const int MAX_V = 20000+5;
typedef int CAP;
const CAP INF = (int)1e9;

struct Edge{ int dst; CAP cap; int rev; };
vector<Edge> adj[MAX_V];
int level[MAX_V];
int done[MAX_V];
void clearedge() { REP(i, MAX_V) adj[i].clear(); }
void addedge(int u, int v, CAP c1, CAP c2) {
  adj[u].push_back( (Edge){v, c1, (int)adj[v].size() + (u == v)} );
  adj[v].push_back( (Edge){u, c2, (int)adj[u].size() - 1} );
}

CAP dinic_dfs(int v, CAP flow, int t) {
  if (v == t || flow == 0) return flow;
  for ( ; done[v] < (int)adj[v].size(); done[v]++) {
    Edge &e = adj[v][done[v]];
    if (level[v] >= level[e.dst]) continue;
    CAP f = dinic_dfs(e.dst, min(flow, e.cap), t);
    if (f > 0) {
      e.cap -= f;
      adj[e.dst][e.rev].cap += f;
      return f;
    }
  }
  return 0;
}

bool dinic_bfs(int s, int t) {
  memset(level, -1, sizeof(level));
  queue<int> q; q.push(s); level[s] = 0;
  while (!q.empty()) {
    int here = q.front(); q.pop();
    for (const Edge &e : adj[here]) {
      if (e.cap > 0 && level[e.dst] == -1) {
        level[e.dst] = level[here] + 1;
        q.push(e.dst);
      }
    }
  }
  return level[t] >= 0;
}

CAP dinic(int s, int t) {
  CAP res = 0;
  while (dinic_bfs(s,t)) {
    memset(done, 0, sizeof(done));
    for (CAP f; (f = dinic_dfs(s, INF, t)) > 0; ) res += f;
  }
  return res;
}
