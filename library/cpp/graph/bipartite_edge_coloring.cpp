// 二部グラフの辺彩色数は最大次数 D と一致する。
// 色の塗り方を具体的に求める。O(nm)
// ECR002 F https://codeforces.com/contest/600/problem/F
//     https://codeforces.com/blog/entry/21827
//     https://www.slideshare.net/catupper/ss-25736611

const int MAX_N = 1005;

int AtoB[MAX_N][MAX_N]; // [index of A][edge color] := index of B
int BtoA[MAX_N][MAX_N]; // [index of B][edge color] := index of A
int color[MAX_N][MAX_N];
int degA[MAX_N];
int degB[MAX_N];

void dfsB(int b, int s, int t);

void dfsA(int a, int s, int t) {
  int b = AtoB[a][s];
  if (b != -1) dfsB(b, t, s);
  swap(AtoB[a][t], AtoB[a][s]);
}

void dfsB(int b, int s, int t) {
  int a = BtoA[b][s];
  if (a != -1) dfsA(a, t, s);
  swap(BtoA[b][t], BtoA[b][s]);
}

void add_edge(int a, int b, int D) {
  for (int d = 0; d < D; d++) {
    if (AtoB[a][d] == -1 && BtoA[b][d] == -1) {
      AtoB[a][d] = b;
      BtoA[b][d] = a;
      return;
    }
  }
  int s = -1, t = -1;
  for (int d = 0; d < D; d++) {
    if (BtoA[b][d] == -1) s = d;
    if (AtoB[a][d] == -1) t = d;
  }
  // aで使っているがbで使われていない色s
  // bで使っているがaで使われていない色t

  // a から始まる s, t, s, t, ... パスの色を反転

  dfsA(a, s, t);
  AtoB[a][s] = b;
  BtoA[b][s] = a;

  return;
}

int main2() {
  CLR(AtoB, -1);
  CLR(BtoA, -1);
  CLR(color, -1);
  CLR(degA, 0);
  CLR(degB, 0);

  int A = nextInt();
  int B = nextInt();
  int M = nextInt();

  vector<pair<int,int>> es;
  REP(m, M) {
    int a = nextInt() - 1;
    int b = nextInt() - 1;
    es.emplace_back(a, b);
    degA[a]++;
    degB[b]++;
  }
  int D = 0;
  REP(a, A) chmax(D, degA[a]);
  REP(b, B) chmax(D, degB[b]);

  for(auto e : es) {
    add_edge(e.first, e.second, D);
  }

  REP(a, A) {
    REP(d, D) {
      int b = AtoB[a][d];
      if (b != -1) {
        color[a][b] = d;
      }
    }
  }

  printf("%d\n", D);
  REP(i, es.size()) {
    if (i > 0) printf(" ");
    printf("%d", (1 + color[es[i].first][es[i].second]));
  }
  printf("\n");

  return 0;
}


int main() {

#ifdef LOCAL
  for (;!cin.eof();cin>>ws)
#endif
    main2();
  return 0;
}
