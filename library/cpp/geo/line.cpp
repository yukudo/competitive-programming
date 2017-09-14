ll gcd(ll a, ll b) {
  return b == 0 ? a : gcd(b, a%b);
}

// (x1, y1) と (x2, y2) を通る直線の方程式 ax + by + c == 0 の {a,b,c} を返す
vector<ll> line(ll x1, ll y1, ll x2, ll y2) {
  if (x1 == x2) { return {1, 0, -x1}; }
  if (y1 == y2) { return {0, 1, -y1}; }
  ll a = (y2 - y1);
  ll b = (x1 - x2);
  ll c = y1*x2 - x1*y2;
  if (a < 0) { a *= -1; b *= -1; c *= -1; }
  ll g = gcd(a, gcd(abs(b), abs(c)));
  return {a/g, b/g, c/g};
}
