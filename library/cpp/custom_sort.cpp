void custom_sort_example() {
  vector<P> v;
  v.push_back( P(3, 1) );
  v.push_back( {4, 1} );
  v.push_back( (P){5, 9} );
  v.push_back( make_pair(2, 6) );
  v.emplace_back( P(5, 3) );
  v.emplace_back( (P){5, 8} );
  v.emplace_back( make_pair(9, 7) );
  v.emplace_back( 9, 3 );

  sort(v.begin(), v.end(), [](const P& a, const P& b) -> bool {
    if (a.second != b.second) return a.second < b.second;
    return a.first < b.first;
  });

  REP(i, v.size()) cout << v[i].first << "," << v[i].second << endl;
}
