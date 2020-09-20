/* エラトステネスの篩 */
const int SIZE = 1000000;
vector<ll> primes;
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

/* 約数の列挙 */
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

/* 素因数分解 */
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

/* n! に含まれる p の個数 */
ll fact_count(ll n, ll p) {
  ll res = 0;
  while (n >= p) {
    res += n / p;
    n /= p;
  }
  return res;
}

// オイラーのφ関数
// 1 から n までの整数で n と互いに素なものの個数
// n = p1^a1 * p2^a2 * ... * pk^ak と素因数分解できるとき
// φ(n) = n*(1-1/p1)*(1-1/p2)...*(1-1/pk)
int totient[MAX_N];
void make_totient() {
  REP(i, MAX_N) totient[i] = i;
  for (int i = 2; i < MAX_N; i++) {
    if (totient[i] == i) { // i is prime
      --totient[i];
      for (int j = i + i; j < MAX_N; j += i) totient[j] -= totient[j] / i;
    }
  }
}

// メビウス関数
// meb[n] = {
//   0 if n が素数の2乗を因数に持つ
//  -1 if n の素因数の個数が odd
//  +1 if n の素因数の個数が even
// }
int mobius[MAX_N];
void make_mobius() {
  for(int i = 0; i < MAX_N; i++) mobius[i] = 1;
  for(int i = 2; i < MAX_N; i++)
   if (isPrime[i])
     for(int j = i; j < MAX_N; j += i)
       if ( j / i % i == 0 ) mobius[j] = 0;
       else mobius[j] *= -1;
  pv(mobius, mobius + 31);
  // 1 1 -1 -1 0 -1 1 -1 0 0 1 -1 0 -1 1 1 0 -1 0 -1 0 1 1 -1 0 0 1 0 0 -1 -1
}


// N の約数におけるメビウス関数の値のmapを返す。 O(√N)
map<int,int> mobius(int N) {
  map<int,int> res;
  vector<int> ps = factorize(N);
  ps.erase(unique(ALL(ps)), ps.end());
  int M = ps.size();
  REP(i, 1 << M) {
    int mu = 1, d = 1;
    REP(j, M) if (i >> j & 1) {
      mu *= -1;
      d *= ps[j];
    }
    res[d] = mu;
  }
  return res;
}

// 1 <= i <= N && gcd(i, K) == 1 を満たす i の総和を求める ABC020D-LCM Rush
ll solve(ll N, ll K) {
  ll ans = 0;
  vector<int> ps = factorize(K); sort(ALL(ps)); ps.erase(unique(ALL(ps)), ps.end());
  int M = ps.size();
  REP(set, 1<<M) {
    ll p = 1, sign = 1;
    REP(i, M) if (set >> i & 1) { p *= ps[i]; sign *= -1; }
    ll n = N/p;
    ans += sign * (n*(n+1)/2 % MOD) * p % MOD;
    ans = (ans % MOD + MOD) % MOD;
  }
  return ans;
}

