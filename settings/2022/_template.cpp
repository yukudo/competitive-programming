#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define REP(i,n) for(int i=0,_n=(int)(n);i<_n;++i)
#define ALL(v) (v).begin(),(v).end()
#define CLR(t,v) memset(t,(v),sizeof(t))
template<class T1,class T2>ostream& operator<<(ostream& os,const pair<T1,T2>&a){return os<<"("<<a.first<<","<<a.second<< ")";}
template<class T>void chmin(T&a,const T&b){if(a>b)a=b;}
template<class T>void chmax(T&a,const T&b){if(a<b)a=b;}
#ifdef LOCAL
template<class T>void pv(T a,T b){for(T i=a;i!=b;++i)cerr<<(*i)<<" ";cerr<<endl;}
#else
template<class T>void pv(T a,T b){}
#endif

ll nextLong() { ll x; scanf("%lld", &x); return x;}

int main2() {
  int N = nextLong();

  ll ans = N;
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
