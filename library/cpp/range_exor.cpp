// [0, L] の数を全て exor した数を返す
// [a, b] の範囲で欲しい時は range(a-1) ^ range(b) とすれば良い
ll range(ll L) {
  switch (L & 3) {
  case 0: return L;
  case 1: return 1;
  case 2: return L + 1;
  case 3: return 0;
  }
}
