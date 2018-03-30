// 座標圧縮
vector<int> normalize(const vector<ll> v) {
  const int N = v.size();
  vector<int> res(N);
  vector<pair<ll,int> > t(N);
  REP(i, N) t[i] = { v[i], i };
  sort(ALL(t));
  int r = 0;
  REP(i, N) {
    r += (i > 0 && t[i - 1].first != t[i].first);
    res[t[i].second] = r;
  }
  return res;
}
