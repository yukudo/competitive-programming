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


// n choose r
ll C[MAX_N][MAX_N];
for (int i = 0; i < MAX_N; i++) {
  for (int j = 0; j <= i; j++) {
    C[i][j] = (j == 0) ? 1 : (C[i-1][j-1] + C[i-1][j]);
    if (C[i][j] >= MOD) C[i][j] -= MOD;
  }
}


const int SZ = 312345;
ll inv[SZ];
ll fact[SZ];
ll fact_inv[SZ];
ll choose(int n, int r) {
  if (n < 0 || r < 0 || n < r) return 0;
  return fact[n] * fact_inv[n-r] % MOD * fact_inv[r] % MOD;
}
// ## 逆元の列挙 O(N)
// これで 1 から N までの逆元が O(N) でもとまります。i * (MOD/i) = MOD - MOD%i を変形すると出てきます。
// https://twitter.com/rng_58/status/312405554339405824
// https://twitter.com/rng_58/status/312413291647492096
{
  inv[1] = 1;
  for (int i = 2; i < SZ; i++) inv[i] = inv[(int) (MOD % i)] * (MOD - MOD / i) % MOD;
  fact[0] = 1;
  for (int i = 1; i < SZ; i++) fact[i] = fact[i-1] * i % MOD;
  fact_inv[0] = 1;
  for (int i = 1; i < SZ; i++) fact_inv[i] = fact_inv[i-1] * inv[i] % MOD;
}
