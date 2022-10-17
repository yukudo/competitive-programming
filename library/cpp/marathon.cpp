#include <bits/stdc++.h>
#include <chrono>
using namespace std;


int xor64() {
  static uint64_t x = 233397374093810282ULL;
  x ^= x<<13;
  x ^= x>>7;
  x ^= x<<17;
  return int(x&0x7fffffff);
}


chrono::system_clock::time_point timer_start = chrono::system_clock::now();
void resetTimer() {
  timer_start = chrono::system_clock::now();
}
double getElapsedSeconds() {
  chrono::system_clock::time_point now = chrono::system_clock::now();
  return chrono::duration_cast<chrono::nanoseconds>(now-timer_start).count()*1e-9;
}


