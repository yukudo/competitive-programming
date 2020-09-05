
// 座標圧縮
// vector<ll> rev; // 圧縮後の値から元の値への写像
vector<int> normalize(const vector<ll> v) {
  const int N = v.size();
  vector<int> res(N);
  vector<pair<ll,int> > t(N);
  // rev = vector<ll>(N);
  REP(i, N) t[i] = { v[i], i };
  sort(ALL(t));
  int r = 0;
  REP(i, N) {
    r += (i > 0 && t[i - 1].first != t[i].first);
    res[t[i].second] = r;
    // rev[r] = t[i].first;
  }
  // rev.erase(rev.begin() + r + 1, rev.end());
  return res;
}
