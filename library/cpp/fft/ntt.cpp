// FFT するとき複素数の N 乗根の代わりに mod 上の原始 N 乗根を使う。
// https://atc001.contest.atcoder.jp/tasks/fft_c
// https://www.slideshare.net/chokudai/fft-49066791/1

const ll MOD = 998244353;
const ll PRIMITIVE_ROOT = 3;
#define SZ(v) ((int)(v).size())

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

void dft(vector<ll>& f, const bool inv) {
  const int N = SZ(f); // N must be power of 2.
  if (N == 1) return;
  vector<ll> f0(N/2), f1(N/2);
  REP(i, N/2) { f0[i] = f[i*2]; f1[i] = f[i*2 + 1]; }
  dft(f0, inv);
  dft(f1, inv);
  ll w1 = mod_pow(PRIMITIVE_ROOT, (MOD-1)/N, MOD);
  if (inv) w1 = mod_inv(w1, MOD);
  ll w = 1;
  REP(i, N) {
    const int i2 = (i < N/2 ? i : i - N/2);
    f[i] = (f0[i2] + w * f1[i2]) % MOD;
    (w *= w1) %= MOD;
  }
}

vector<ll> mul(vector<ll> g, vector<ll> h) {
  int N = 1;
  while (N < SZ(g) + SZ(h) - 1) N *= 2;
  while (SZ(g) < N) g.push_back(0);
  while (SZ(h) < N) h.push_back(0);
  dft(g, false);
  dft(h, false);
  vector<ll> ff(N);
  REP(i, N) ff[i] = (g[i] * h[i]) % MOD;
  dft(ff, true);
  ll invN = mod_inv(N, MOD);
  REP(i, N) (ff[i] *= invN) %= MOD;
  return ff;
}

int main2() {
  int N; cin >> N;
  vector<ll> A(N+1), B(N+1);
  REP(i, N) cin >> A[i+1] >> B[i+1];

  vector<ll> res = mul(A, B);
  for (int i = 1; i <= 2*N; i++) {
    printf("%d\n", (int)res[i]);
  }
  return 0;
}

