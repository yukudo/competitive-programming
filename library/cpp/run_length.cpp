template<class T>
vector<pair<T, ll>> runLength(const vector<T>& xs) {
  vector<pair<T, ll>> res;
  for (auto x : xs) {
    if (res.empty() || res.back().first != x) {
      res.push_back({x, 1});
    } else {
      ++res.back().second;
    }
  }
  return res;
}

