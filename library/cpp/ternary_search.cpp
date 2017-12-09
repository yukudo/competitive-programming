// 凸関数の最小値（または最大値）を求める
ll lo = 0;
ll hi = 1LL << 60;
while (hi - lo >= 3) {
  ll l = (lo * 2 + hi) / 3;
  ll r = (lo + hi * 2) / 3;
  if (f(l) > f(r)) lo = l; else hi = r; // min: > , max: <
}
ll minVal = f(lo);
for (ll i = lo + 1; i <= hi; i++)
  minVal = min(minVal, f(i));
return minVal;
