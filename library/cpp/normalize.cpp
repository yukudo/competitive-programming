// 座標圧縮
vector<int> normalize(vector<int> v) {
  const int N = v.size();
  vector<pair<int,int> > t(N);
  REP(i, N) {
    t[i].first = v[i];
    t[i].second = i;
  }
  sort(ALL(t));
  int r = 0;
  REP(i, N) {
    r += (i > 0 && t[i - 1].first != t[i].first);
    v[t[i].second] = r;
  }
  return v;
}
