// convex hull trick

const int MAX_N = 212345;
ll h[MAX_N];
ll dp[MAX_N];

struct Line {
  ll a, b;
  ll f(ll x) {
    return a*x + b;
  }
};

bool check(Line l1, Line l2, Line l3) {
  return (l1.a - l2.a)*(l3.b - l2.b) <= (l2.b - l1.b)*(l2.a - l3.a);
}


// EDPC Z Frog 3 https://atcoder.jp/contests/dp/tasks/dp_z
int main2() {
  int N; cin >> N;
  ll C; cin >> C;
  REP(i, N) cin >> h[i+1];

  deque<Line> deq;
  dp[1] = 0;
  for (int i = 2; i <= N; i++) {
    Line line = (Line){-2 * h[i-1], (h[i-1] * h[i-1] + dp[i-1])};
    while (deq.size() >= 2 && check(deq[deq.size()-2], deq[deq.size()-1], line)) deq.pop_back();
    deq.push_back(line);
    while (deq.size() >= 2 && deq[0].f(h[i]) >= deq[1].f(h[i])) deq.pop_front();
    ll res = deq[0].f(h[i]);
    res += h[i] * h[i] + C;
    dp[i] = res;
  }
  cout << dp[N] << endl;
  return 0;
}
    
