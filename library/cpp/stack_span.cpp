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



void stack_span(const vector<int> &v, vector<int>&lt, vector<int>& gt) {
  const int n = v.size();
  lt.assign(n, n);
  gt.assign(n, n);
  vector<int> l, g;
  REP(i, n) {
    while(!l.empty() && v[l.back()] > v[i]) {
      lt[l.back()] = i;
      l.pop_back();
    }
    l.push_back(i);
    while(!g.empty() && v[g.back()] < v[i]) {
      gt[g.back()] = i;
      g.pop_back();
    }
    g.push_back(i);
  }
}

int main() {
  int N = nextInt();
  vector<int> v(N);
  REP(i, N) v[i] = nextInt();

  vector<int> lt, gt;
  vector<int> blt, bgt;

  stack_span(v, lt, gt);
  reverse(ALL(v));
  stack_span(v, blt, bgt);
  REP(i, N) blt[i] = N - 1 - blt[i];
  REP(i, N) bgt[i] = N - 1 - bgt[i];
  reverse(ALL(v));
  reverse(ALL(blt));
  reverse(ALL(bgt));

printf("                                          : ");pv(ALL(v));
printf("右を見て最初にぶつかる自分より低いものの添え字: ");pv(ALL(lt));
printf("右を見て最初にぶつかる自分より高いものの添え字: ");pv(ALL(gt));
printf("左を見て最初にぶつかる自分より低いものの添え字: ");pv(ALL(blt));
printf("左を見て最初にぶつかる自分より高いものの添え字: ");pv(ALL(bgt));
}
