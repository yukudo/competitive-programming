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

// https://atcoder.jp/contests/intro-heuristics/submissions/14822072
class RandXor{public:
RandXor() { init(); }
void init() { x = 123456789; y = 362436069; z = 521288629; w = 88675123; }
unsigned int rand() { unsigned int t; t = (x ^ (x << 11)); x = y; y = z; z = w; return(w = (w ^ (w >> 19)) ^ (t ^ (t >> 8))); }
unsigned int next() { return rand(); }
int nextInt(int num) { return rand() % num; }
int next(int a, int b) { return a + (rand() % (b - a)); } // [a,b)
template <class T> void randomShuffle(vector <T> &a) { const int n = a.size(); for (int i = n - 1; i > 0; --i) {  swap(a[i], a[nextInt(i + 1)]); } }
private: unsigned int x, y, z, w;};

RandXor randXor;
int randint(int a, int b) { // a <= x <= b. It is same as python's random.randint(a, b).
  return randXor.next(a, b+1);
}

int main(int argc, char **argv) {
  if (argc >= 2 && string(argv[1]) == "--create") {
    // generate stress test cases.
    int A = 5;
    int B = 5;
    int C = 5;
    for (int a = 1; a <= A; a++) {
      for (int b = 1; b <= B; b++) {
        for (int c = 1; c <= C; c++) {
          cout << a << " " << b << " " << c << endl;
        }
      }
    }
    return 0;
  }

#ifdef LOCAL
  for (;!cin.eof();cin>>ws)
#endif
    main2();
  return 0;
}
