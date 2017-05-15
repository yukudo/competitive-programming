#include "message.h"
#include "problem_name.h"

// int NumberOfNodes();
// int MyNodeId();
// void PutChar(int target, char value);
// void PutInt(int target, int value);
// void PutLL(int target, long long value);
// void Send(int target);
// int Receive(int source);
// char GetChar(int source);
// int GetInt(int source);
// long long GetLL(int source);

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define REP(i,n) for(int i=0,_n=(int)(n);i<_n;++i)
template<class T>bool chmin(T&a,const T&b){if(a<=b)return false;a=b;return true;}
template<class T>bool chmax(T&a,const T&b){if(a>=b)return false;a=b;return true;}

int NODES, MY;

void solve() {

}

int main() {
  NODES = NumberOfNodes();
  MY = MyNodeId();
  solve();
  return 0;
}
