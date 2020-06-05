
/**
 * 長方形(0,0)-(x,y)たちの和集合の面積
 * JOI 春合宿 2012 Day1 Fish
 */
struct Fish {
  ll area;
  map<ll, ll> m;
  Fish() {
    area = 0;
    m[1LL<<60] = 0;
    m[0] = 1LL<<60;
  }
  void add(const ll x, const ll y) {
    ll yy = m.lower_bound(x)->second;
    if (y <= yy) return;
    for (;;) {
      auto pit = prev(m.lower_bound(x));
      ll px = pit->first, py = pit->second;
      if (py > y) break;
      m.erase(pit);
      area -= (px - prev(m.lower_bound(x))->first) * (py - yy);
    }
    area += (x - prev(m.lower_bound(x))->first) * (y - yy);
    m[x] = y;

    // cout << "(" << x << ", " << y << ")  area=" << area << endl;
    // pv(ALL(m));
  }
};
