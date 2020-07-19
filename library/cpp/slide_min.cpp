// スライド最小値
// 蟻本のアルゴリズム。
// 幅k=10の最小値を求めるとして、1,3,6,2,4,... という入力数列を左から順に見ていったときに、
// 2に着いた時点で3,6は捨てても構わないよねということを利用してdequeでがんばる 
// 
// K : 区間の幅
// push(val, pos) : pos の位置に val を追加し、区間の右端が pos になるように移動させる。
// get(pos) : 区間の右端が pos になるように移動させて、そのときの最小値を返す。
// get(pos, &isEmpty) : deque が空のときには isEmpty に true がセットされ、無効な値が返される。
// 
// push/get で指定する pos は時間とともに単調増加すること。
//
struct SlideMin {
  int K;
  deque<ll> idx, data;

  SlideMin(int K) {
    this->K = K;
  }

  void move(int pos) {
    while (!idx.empty() && pos - idx.front() >= K) {
      idx.pop_front();
      data.pop_front();
    }
  }

  void push(ll val, int pos) {
    move(pos);
    while (!data.empty() && data.back() >= val) { // min: >=, max: <=
      idx.pop_back();
      data.pop_back();
    }
    idx.push_back(pos);
    data.push_back(val);
  }

  ll get(int pos) {
    bool dummy;
    return get(pos, dummy);
  }

  ll get(int pos, bool& empty) { // pos: right edge of the window (closed interval).
    move(pos);
    empty = data.empty();
    if (empty) return 0; // return value is meaningless.
    return data.front();
  }

};
