struct RollingHash {
  using HashType = tuple<ll,ll,ll>;

  const ll mod1 = 999999893;
  const ll mod2 = 999999929;
  const ll mod3 = 999999937;
  const ll b1 = 3422539;
  const ll b2 = 1245103;
  const ll b3 = 22961;
  vector<ll> h1, h2, h3;
  vector<ll> pow1, pow2, pow3;

  RollingHash(const string &s) {
    const int n = s.size();
    h1.assign(n+1, 0);
    h2.assign(n+1, 0);
    h3.assign(n+1, 0);
    pow1.assign(n+1, 1);
    pow2.assign(n+1, 1);
    pow3.assign(n+1, 1);
    REP(i, n) {
      h1[i+1] = (h1[i] * b1 + s[i]) % mod1;
      h2[i+1] = (h2[i] * b2 + s[i]) % mod2;
      h3[i+1] = (h3[i] * b3 + s[i]) % mod3;
      pow1[i+1] = pow1[i] * b1 % mod1;
      pow2[i+1] = pow2[i] * b2 % mod2;
      pow3[i+1] = pow3[i] * b3 % mod3;
    }
  }

  HashType get(int l, int r) {
    ll v1 = ((h1[r] - h1[l] * pow1[r-l]) % mod1 + mod1) % mod1;
    ll v2 = ((h2[r] - h2[l] * pow2[r-l]) % mod2 + mod2) % mod2;
    ll v3 = ((h3[r] - h3[l] * pow3[r-l]) % mod3 + mod3) % mod3;
    return HashType {v1, v2, v3};
  }
};
