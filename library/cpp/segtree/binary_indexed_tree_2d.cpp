// 点に加算、範囲の和
// 利用するときは 0-indexed、内部的には1-indexed
// 閉区間なので注意
using Val = ll;
const int SIZE = 5005;
Val tree[SIZE+1][SIZE+1];

// 点(x, y) に val を加算
void add(int x, int y, Val val) {
  for (int tx = x+1; tx <= SIZE; tx+=tx&-tx) {
    for (int ty = y+1; ty <= SIZE; ty+=ty&-ty) {
      tree[tx][ty] += val;
    }
  }
}
// return sum of rectangle (0,0), (x,y) inclusive
Val sum(int x, int y) {
  Val res = 0;
  for (int tx=x+1; tx>0; tx-=tx&-tx) {
    for (int ty=y+1; ty>0; ty-=ty&-ty) {
      res += tree[tx][ty];
    }
  }
  return res;
}
// return sum of rectangle [(x0,y0), (x1,y1)] inclusive
Val get(int x0, int y0, int x1, int y1) {
  return sum(x1, y1) - sum(x1, y0-1) - sum(x0-1, y1) + sum(x0-1, y0-1);
}
Val get(int x, int y) {
  return get(x, y, x, y);
}
