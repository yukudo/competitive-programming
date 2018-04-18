// 高速フーリエ変換により多項式乗算をする。解説そのまま。
// https://atc001.contest.atcoder.jp/tasks/fft_c
// https://www.slideshare.net/chokudai/fft-49066791/1

const double PI2 = 2*acos(-1);
#define SZ(v) ((int)(v).size())
typedef complex<double> C;
 
void dft(vector<C>& f, const bool inv) {
  const int N = SZ(f); // N must be power of 2.
  if (N == 1) return;
  vector<C> f0(N/2), f1(N/2);
  REP(i, N/2) { f0[i] = f[i*2]; f1[i] = f[i*2 + 1]; }
  dft(f0, inv);
  dft(f1, inv);
  const C w1 = polar(1.0, (inv?-1:1)*PI2/N);
  C w = 1;
  REP(i, N) {
    const int i2 = (i < N/2 ? i : i - N/2);
    f[i] = f0[i2] + w * f1[i2];
    w *= w1;
  }
}
 
vector<C> mul(vector<C> g, vector<C> h) {
  int N = 1;
  while (N < SZ(g) + SZ(h) - 1) N *= 2;
  while (SZ(g) < N) g.push_back(0);
  while (SZ(h) < N) h.push_back(0);
  dft(g, false);
  dft(h, false);
  vector<C> ff(N);
  REP(i, N) ff[i] = g[i] * h[i];
  dft(ff, true);
  REP(i, N) ff[i] /= N;
  return ff;
}
 
int main2() {
  int N; cin >> N;
  vector<C> A(N+1), B(N+1);
  REP(i, N) cin >> A[i+1] >> B[i+1];
 
  vector<C> res = mul(A, B);
  for (int i = 1; i <= 2*N; i++) {
    printf("%d\n", (int)round(res[i].real()));
  }
  return 0;
}
