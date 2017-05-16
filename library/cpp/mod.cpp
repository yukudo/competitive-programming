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

// ## 逆元の列挙 O(N)
// これで 1 から N までの逆元が O(N) でもとまります。i * (MOD/i) = MOD - MOD%i を変形すると出てきます。
// https://twitter.com/rng_58/status/312405554339405824
// https://twitter.com/rng_58/status/312413291647492096
{
  ll inv[N];
  inv[1] = 1;
  for (int i = 2; i < N; i++) inv[i] = inv[(int) (MOD % i)] * (MOD - MOD / i) % MOD;
}
