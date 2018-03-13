/* エラトステネスの篩 */
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

/*
 * n! に含まれる p の個数
 */
ll fact_count(ll n, ll p) {
  ll res = 0;
  while (n >= p) {
    res += n / p;
    n /= p;
  }
  return res;
}
