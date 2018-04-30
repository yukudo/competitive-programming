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

struct Trie {
  Trie* ch[2] = { nullptr, nullptr };
  int sz = 0;
};


const int MAX_N = 1123456;
int a[MAX_N];

void add(Trie* node, int v) {
  for (int depth = 29; depth >= 0; depth--) {
    node->sz++;
    int k = v >> depth & 1;
    if (node->ch[k] == nullptr) { node->ch[k] = new Trie(); }
    node = node->ch[k];
  }
  node->sz++;
}

int sz(Trie* node) {
  if (node == nullptr) return 0;
  return node->sz;
}

ll count(Trie* node, int dir, int v) {
  ll res = 0;
  for (int depth = 29; depth >= 0; depth--) {
    int k = v >> depth & 1;
    int l = dir >> depth & 1;
    if (k == 0) {
      res += sz(node->ch[1^l]);
      node = node->ch[0^l];
    } else {
      node = node->ch[1^l];
    }
    if (node == nullptr) break;
  }
  res += sz(node);
  return res;
}

int naive(int N, int K) {
  int res = 0;
  for (int i = 0; i < N; i++) {
    int x = 0;
    for (int j = i; j < N; j++) {
      x ^= a[j];
      if (x >= K) res++;
    }
  }
  cout << res << endl;
  return res;
}


// ECR012 E. Beautiful Subarrays
// http://codeforces.com/contest/665/problem/E

int main2() {
  int N = nextInt();
  int K = nextInt();
  REP(i, N) a[i] = nextInt();
  ll ans = 0;

  // naive(N, K);

  Trie* ROOT = new Trie();

  int sum = 0;
  add(ROOT, 0);
  REP(i, N) {
    sum ^= a[i];
    ans += count(ROOT, sum, K);
    // cout << "ans=" << ans << endl;
    add(ROOT, sum);
  }
  cout << ans << endl;
  return 0;
}

int main() {
  for (;!cin.eof();cin>>ws)
    main2();
  return 0;
}