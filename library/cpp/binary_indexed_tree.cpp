
// 最上位ビットを残してあとは 0 にする
int highestOneBit(unsigned int i) {
  i |= (i >>  1);
  i |= (i >>  2);
  i |= (i >>  4);
  i |= (i >>  8);
  i |= (i >> 16);
  return i - (i >> 1);
}

// 点に加算、範囲の和
// 内部的には 1-based であるが、利用するときには 0-based な実装
struct BIT {
  int n;
  vector<ll> tree;
  BIT(int n):n(n),tree(n+1) {} 
  void fill(ll val) {
    REP(i, n+1) tree[i] = (i&-i) * val;
  }
  void add(int idx, ll val) {
    for (int x=idx+1; x<=n; x+=x&-x) tree[x] += val;
  }
  // sum[0, idx]
  ll range(int idx) {
    ll sum=0;
    for (int x=idx+1; x>0; x-=x&-x) sum += tree[x];
    return sum;
  }
  // sum[a, b]
  ll range(int a, int b) {
    return range(b) - range(a - 1);
  }
  // sum [0, i] が k より大きい最小の i を求める
  int get(ll k) {
    int p = highestOneBit(n);
    for (int q = p; q > 0; q >>= 1, p |= q) {
      if (p >= n || k < tree[p]) p ^= q;
      else k -= tree[p];
    }
    return p;
  }
};
