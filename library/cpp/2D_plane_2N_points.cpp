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

// 問題：
// 2次元平面に赤い点と青い点が合計N個ある。
// 青い点は、自身よりも左下の領域にある赤い点とペアを作ることができる。
// 点は高々1つのペアに属することができる。
// 作れるペアの最大個数を求めよ。 ARC092C, ARC046C
// 解法：
// 全部の点をx座標でソートする。
// 縦線を左から右に移動させながら、青い点が出たら「その青い点とペアにできるその時点で最もy座標が大きい赤い点を選ぶ」を繰り返せば良い。
// O(NlogN)

struct P {
  int color, x, y;
};

const int MAX_N = 312345;
P p[MAX_N];

int solve(int N) {
  sort(p, p+N, [](const P&a, const P&b){
    if (a.x != b.x) return a.x < b.x;
    if (a.color != b.color) return a.color < b.color;
    return a.y < b.y;
  });
  int ans = 0;
  multiset<int> st;
  REP(i, N) {
    if (p[i].color == 0) {
      st.insert(p[i].y);
    }
    if (p[i].color == 1) {
      auto it = st.upper_bound(p[i].y);
      if (it != st.begin()) {
        --it;
        if ((*it) <= p[i].y) {
          st.erase(it);
          ans++;
        }
      }
    }
  }
  return ans;
}

int main2() {
  // ARC046C 合コン大作戦
  int N = nextInt();
  int M = nextInt();
  REP(i, N) {
    int a = nextInt();
    int b = nextInt();
    p[i] = (P){1, -b, a};
  }
  REP(i, M) {
    int c = nextInt();
    int d = nextInt();
    p[N+i] = (P){0, -c, d};
  }
  int ans = solve(N+M);
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
