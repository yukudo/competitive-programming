// for (int k = 1; k <= n; k++) ans += g(n/k);
// x=n/k の値が同じものが何回登場するかを数えて一度だけ g を呼び出すと速い
ll solve(int n) {
  ll ans = 0;
  int x;
  for (x = 1; x * x < n; x++) {
    int c = n/x - n/(x+1);
    ans += c * g(x);
  }
  for (int k = 1; k * x <= n; k++) ans +=g(n/k);
  return ans;
}
