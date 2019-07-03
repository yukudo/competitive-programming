#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define REP(i,n) for(int i=0,_n=(int)(n);i<_n;++i)
#define ALL(v) (v).begin(),(v).end()
#define CLR(t,v) memset(t,(v),sizeof(t))
template<class T1,class T2>ostream& operator<<(ostream& os,const pair<T1,T2>&a){return os<<"("<<a.first<<","<<a.second<< ")";}
template<class T>void pv(T a,T b){for(T i=a;i!=b;++i)cout<<(*i)<<" ";cout<<endl;}
template<class T>void chmin(T&a,const T&b){if(a>b)a=b;}
template<class T>void chmax(T&a,const T&b){if(a<b)a=b;}


int nextInt() { int x; scanf("%d", &x); return x;}
ll nextLong() { ll x; scanf("%lld", &x); return x;}

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


int teccid[MAX_N];
int teccnum;
void dfs2(int u, int id) {
  teccid[u] = id;
  for (int v : g[u]) if (teccid[v] == -1 && !isBridge(u, v)) dfs2(v, id);
}
// 二重辺連結成分分解(two edge connected components)
// 橋を使わずに到達できる点をdfsで求める
void tecc(int N) {
  CLR(teccid, -1);
  teccnum = 0;
  REP(i, N) if (teccid[i] == -1) {
    dfs2(i, teccnum);
    teccnum++;
  }
}



vector<int> h[MAX_N];
bool vis[MAX_N];
pair<int,int> dfs3(int u, int p, int d) {
  vis[u] = true;
  pair<int,int> res = {d, u};
  for (int v : h[u]) if (v != p && !vis[v]) {
    chmax(res, dfs3(v, u, d+1));
  }
  return res;
}


// ECR046 E - We Need More Bosses https://codeforces.com/contest/1000/problem/E
// n 頂点 m 辺の連結な無向単純グラフが与えられる。
// 2 点 s, t に対し「その 1 辺を壊したら s と t とが繋がらなくなる」ような辺をクリティカルエッジと呼ぶ。
// うまく s, t を選んだときのクリティカルエッジの本数の最大値を求めよ。
// 二重辺連結成分分解してサイクルを縮約すると木になる。その木での直径が答え。
int main2() {
  REP(i, MAX_N) g[i].clear();

  int N = nextInt();
  int M = nextInt();
  REP(i, M) {
    int a = nextInt() - 1;
    int b = nextInt() - 1;
    g[a].push_back(b);
    g[b].push_back(a);
  }

  lowlink(N);
  tecc(N);

  // 二重連結成分を1頂点に縮約した木を陽に作る
  REP(i, MAX_N) h[i].clear();
  set<pair<int,int>> es;
  REP(u, N) {
    for (int v : g[u]) if (u < v) {
      int a = teccid[u];
      int b = teccid[v];
      if (a > b) swap(a, b);
      if (a != b && es.count({a, b}) == 0) {
        es.insert({a, b});
        h[a].push_back(b);
        h[b].push_back(a);
      }
    }
  }
  // 木の直径
  CLR(vis, 0);
  auto res = dfs3(0, -1, 0); // dist, pos
  CLR(vis, 0);
  auto res2 = dfs3(res.second, -1, 0);
  int ans = res2.first;
  cout << ans << endl;
  return 0;
}

int main() {

#ifdef LOCAL
  for (;!cin.eof();cin>>ws)
#endif
    main2();
  return 0;
}
