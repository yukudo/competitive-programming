const int MAX_V = 20000+5;
using CAP = int;
using COST = int;
const int INF = (int)1e9;

struct State {
  COST dist;
  int pos;
  bool operator < (const State &o) const {
    return dist > o.dist; // reverse order
  }
};
struct Edge{ int to; CAP cap; COST cost; int rev; };
vector<Edge> adj[MAX_V];
COST potential[MAX_V];
COST dist[MAX_V];
int prevv[MAX_V];
int preve[MAX_V];
void clearedge() { REP(i, MAX_V) adj[i].clear(); }
void addedge(int u, int v, CAP cap, COST cost) {
  adj[u].push_back( (Edge){v, cap, cost, (int)adj[v].size() + (u == v)} );
  adj[v].push_back( (Edge){u, 0, -cost, (int)adj[u].size() - 1} );
}

// sからtへ流量 flow を流す最小コストを返す。
// 流せない場合は INF を返す
COST mincost_maxflow(int s, int t, CAP flow) {
  vector<int> vs;
  REP(i, MAX_V) if (adj[i].size()) vs.push_back(i);
  COST res = 0;
  for (int v : vs) potential[v] = 0;
  while (flow > 0) {
    for (int v : vs) dist[v] = INF;
    priority_queue<State> q;
    q.push({0, s});
    dist[s] = 0;
    while (!q.empty()) {
      State crt = q.top(); q.pop();
      if (dist[crt.pos] < crt.dist) continue;
      REP(i, adj[crt.pos].size()) {
        const Edge&e = adj[crt.pos][i];
        COST n_dist = crt.dist + e.cost + potential[crt.pos] - potential[e.to];
        if (e.cap > 0 && dist[e.to] > n_dist) {
          dist[e.to] = n_dist;
          prevv[e.to] = crt.pos;
          preve[e.to] = i;
          q.push({dist[e.to], e.to});
        }
      }
    }
    if (dist[t] == INF) return INF;
    for (int v : vs) potential[v] += dist[v];
    CAP f = flow;
    for (int v = t; v != s; v = prevv[v]) {
      f = min(f, adj[prevv[v]][preve[v]].cap);
    }
    for (int v = t; v != s; v = prevv[v]) {
      Edge &e = adj[prevv[v]][preve[v]];
      e.cap -= f;
      adj[v][e.rev].cap += f;
    }
    flow -= f;
    res += f * potential[t];
  }
  return res;
}
