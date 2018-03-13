#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define REP(i,n) for(int i=0,_n=(int)(n);i<_n;++i)
#define ALL(v) (v).begin(),(v).end()
template<class T>void pv(T a,T b){for(T i=a;i!=b;++i)cout<<(*i)<<" ";cout<<endl;}

const ll MOD = (ll)(1e9+7);

const int SIZE = 1000000;
vector<int> primes;
bool isPrime[SIZE];

void make_primes() {
  if (primes.size() > 0) return;
  memset(isPrime, true, sizeof(isPrime));
  isPrime[0] = isPrime[1] = false;
  for (int i = 2; i * i < SIZE; i++) 
    if (isPrime[i])
      for (int j = i * i; j < SIZE; j += i)
        isPrime[j] = false;
  REP(i, SIZE) if (isPrime[i]) primes.push_back(i);
}

vector<int> divisors(int n) {
  vector<int> ds;
  for(int d = 1; d * d <= n; d++) {
    if (n % d == 0) {
      ds.push_back(d);
      if (d * d != n) ds.push_back(n/d);
    }
  }
  sort(ds.begin(), ds.end());
  return ds;
}

vector<int> factorize(int n) {
  vector<int> ps;
  for (int i = 0; primes[i] * primes[i] <= n; i++) {
    while (n % primes[i] == 0) {
      ps.push_back(primes[i]);
      n /= primes[i];
    }
  }
  if (n > 1) ps.push_back(n);
  sort(ps.begin(), ps.end());
  return ps;
}

ll gcd(ll a, ll b) {
  return b == 0 ? a : gcd(b, a%b);
}

ll mod_pow(ll a, ll b, ll p) {
  ll res = 1;
  while (b > 0) {
    if (b & 1) res = (res * a) % p;
    a = (a * a) % p;
    b >>= 1;
  }
  return res;
}

ll mod_inv(ll a, ll p) {
  return mod_pow(a % p, p - 2, p);
}

ll naive(int N, int M) {
  ll ans = 0;
  for (int k = 0; k < N; k++) {
    ans += mod_pow(M, gcd(k, N), MOD);
    ans %= MOD;
  }
  return ans * mod_inv(N, MOD) % MOD;
}

ll fast(int N, int M) {
  ll ans = 0;
  vector<int> ds = divisors(N);
  vector<int> ps = factorize(N);
  ps.erase(unique(ALL(ps)), ps.end());
  for (auto d : ds) {
    const ll Nd = N / d;
    ll euler = Nd;
    for (auto p : ps) if (Nd % p == 0) euler = euler / p * (p - 1);
    ans += euler * mod_pow(M, d, MOD) % MOD;
    ans %= MOD;
  }
  return ans * mod_inv(N, MOD) % MOD;
}

// 
// 以下のコードは愚直にやるとO(n)かかる
// for (int k = 0; k < n; k++) ans += f(gcd(k, n));
// 
// gcd(k, n) = d となる k が何個あるかを d ごとに求めて一度だけ f() を呼び出せば速い。
// この回数はオイラーの totient 関数を用いて φ(n/d) である。
// 

int main() {
  make_primes();
  for (int n = 1; n <= 1000; n++) {
    for (int m = 1; m <= 1000; m++) {
      ll ans1 = naive(n, m);
      ll ans2 = fast(n, m);
      if (ans1 != ans2) cout << n << " " << m << "=>" << ans1 << " " << ans2 << endl;
    }
  }
  return 0;
}
