/*
 * 約数の列挙
 */
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
