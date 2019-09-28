#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define REP(i,n) for(int i=0,_n=(int)(n);i<_n;++i)
#define ALL(v) (v).begin(),(v).end()
template<class T1,class T2>ostream& operator<<(ostream& os,const pair<T1,T2>&a){return os<<"("<<a.first<<","<<a.second<< ")";}
template<class T>void pv(T a,T b){for(T i=a;i!=b;++i)cout<<(*i)<<" ";cout<<endl;}
template<class T>bool chmin(T&a,const T&b){return a>b?(a=b,1):0;}
template<class T>bool chmax(T&a,const T&b){return a<b?(a=b,1):0;}

int nextInt() { int x; scanf("%d", &x); return x;}

const int MAX_N = 100000 + 10;

/**
* Sparse Table による RMQ の実装。
* 区間のmin
* 構築O(nlogn), クエリO(1)
* 更新ができない。
* SegmentTreeによる実装よりも定数倍がかなり高速。
*/
struct RMQStatic {
  int *a;
  int dp_min[20][MAX_N * 2 + 10]; // [i][j] := answer index of start_pos == j, len == 2^i

  int log2(int b) {return 31 - __builtin_clz(b);}

  // O(NlogN)
  void build(int* a, int N) {
    this->a = a;
    int M = log2(N) + 1;
    REP(i, N) dp_min[0][i] = i;
    for (int i = 1, len = 1; i < M; i++, len <<= 1) {
      for (int j = 0; j + len < N; j++) {
        {
          int s = dp_min[i - 1][j];
          int t = dp_min[i - 1][j + len];
          dp_min[i][j] = a[s] <= a[t] ? s : t;
        }
      }
    }
  }

  // O(1)
  // [from..to]の間で最小の値の添字を返す。複数ある場合は一番最初のを返す
  int query(int from, int to) {
    int k = log2(to - from + 1);
    int s = dp_min[k][from];
    int t = dp_min[k][to - (1 << k) + 1];
    return a[s] <= a[t] ? s : t;
  }
};

vector<int> g[MAX_N];

int nod[MAX_N * 2 + 10]; // dfsして i 番目に訪問した頂点の番号
int dep[MAX_N * 2 + 10]; // dfsして i 番目に訪問した頂点の深さ
int apr[MAX_N]; // nod において頂点 v が始めに出現する添字

void dfs(int v, int prev, int d, int& sp) {
  if (apr[v] == -1)
    apr[v] = sp;
  nod[sp] = v; dep[sp] = d; sp++;
  for (int u : g[v]) if (u != prev) {
    dfs(u, v, d + 1, sp);
    nod[sp] = v; dep[sp] = d; sp++;
  }
}

RMQStatic rmq;

// 頂点 a と頂点 b の距離を返す
int dist(int a, int b) {
  int lca = rmq.query(min(apr[a], apr[b]), max(apr[a], apr[b]));
  return (dep[apr[a]] - dep[lca]) + (dep[apr[b]] - dep[lca]);
}

// http://abc014.contest.atcoder.jp/tasks/abc014_4
int main2() {
  int N = nextInt();
  REP(i, N) g[i].clear();
  REP(_, N-1) {
    int x = nextInt() - 1;
    int y = nextInt() - 1;
    g[x].push_back(y);
    g[y].push_back(x);
  }

  int sp = 0;
  memset(apr, -1, sizeof(apr));
  dfs(0, -1, 0, sp);

  rmq.build(dep, sp);

  int Q = nextInt();
  REP(_, Q) {
    int a = nextInt() - 1;
    int b = nextInt() - 1;
    printf("%d\n", dist(a, b) + 1);
  }
  return 0;
}

int main() {
  for (;!cin.eof();cin>>ws) main2();
  return 0;
}
