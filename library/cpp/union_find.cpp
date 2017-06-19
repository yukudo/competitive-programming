struct UnionFind {
  vector<int> data;
  UnionFind(int size) : data(size, -1) { }
  bool link(int x, int y) { //新たな併合を行うとtrue
    x = root(x); y = root(y);
    if (x != y) {
      if (data[y] < data[x]) swap(x, y);
      data[x] += data[y]; data[y] = x;
    }
    return x != y;
  }
  int root(int x) { // 代表元を返す
    return data[x] < 0 ? x : data[x] = root(data[x]);
  }
  int size(int x) { // 要素xが含まれる集合の大きさ
    return -data[root(x)];
  }
  bool same(int x, int y) { // 同じ集合ならtrue
    return root(x) == root(y);
  }
  int num() { // 異なる集合の数
    int res = 0;
    REP(i, data.size()) res += root(i) == i;
    return res;
  }
};
