// BIT を２本持つことによる 範囲add, 範囲sum 
// 蟻本参照。
const int SIZE = 100000 + 10;
BIT bit0(SIZE);
BIT bit1(SIZE);
// 範囲add : [l, r] それぞれに x を加える
void add(int l, int r, ll x) {
  bit0.add(l, -x*(l-1));
  bit1.add(l, x);
  bit0.add(r+1, x*r);
  bit1.add(r+1, -x);
}
// sum[0, i]
ll get(int i) {
  return bit1.range(i) * i + bit0.range(i);
}
