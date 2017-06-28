#include <complex>
using namespace std;

typedef complex<double> P;
const double PI = acos(-1.0);
const double EPS = 1e-10;

inline double dot(P a, P b) {return real(conj(a)*b);}
inline double cross(P a, P b) {return imag(conj(a)*b);}
inline int signum(double x) {return x > EPS ? +1 : x < -EPS ? -1 : 0;}

namespace std {
  bool operator < (const P& a, const P& b) {
    return real(a) != real(b) ? real(a) < real(b) : imag(a) < imag(b);
  }
}

int ccw(P a, P b, P c) {
  // return signum(cross(b - a, c - a));
  b -= a; c -= a;
  if (cross(b, c) > 0)   return +1;       // counter clockwise
  if (cross(b, c) < 0)   return -1;       // clockwise
  if (dot(b, c) < 0)     return +2;       // c--a--b on line
  if (norm(b) < norm(c)) return -2;       // a--b--c on line
  return 0;
}

// 2直線の直行判定 : a⊥b <=> dot(a, b) = 0
bool isOrthogonal(P a1, P a2, P b1, P b2){
  return abs(dot(a1-a2, b1-b2)) < EPS;
}

// 2直線の平行判定 : a//b <=> cross(a, b) = 0
bool isParallel(P a1, P a2, P b1, P b2){
  return abs( cross( a1-a2 , b1-b2 ) ) < EPS;
}

// 点cが直線ab上にあるか
bool isIntersectLP(P a, P b, P c){
  return abs(cross(b-a, c-a)) < EPS;
}

// 点cが線分ab上にあるか : |a-c| + |c-b| <= |a-b| なら線分上 
bool isIntersectSP(P a, P b, P c){
  return (abs(a-c) + abs(c-b) < abs(a-b) + EPS);
}

// 直線aと直線bの交差判定
bool isIntersectLL(P a,P b,P c,P d){
  return abs(cross(b-a, d-c)) > EPS || // non-parallel
         abs(cross(b-a, c-a)) < EPS;   // same line
}

// 直線abと線分cdの交差判定
bool isIntersectLS(P a, P b, P c, P d){
  return
    cross(b-a, c-a) *      //c is left of ab
    cross(b-a, d-a) < EPS; //d is right of ab
}

// 線分と線分の交差判定。端点が重なってもtrue
bool isIntersectSS(P a1, P a2, P b1, P b2){
  return ccw(a1,a2,b1) * ccw(a1,a2,b2) <= 0 &&
         ccw(b1,b2,a1) * ccw(b1,b2,a2) <= 0;
}

// 凸包
vector<P> convexHull(vector<P> ps){
  int N = (int)ps.size();
  int k = 0;
  sort(ps.begin() , ps.end());
  vector<P> ch(2 * N);
  for(int i=0; i < N; ch[k++] = ps[i++] )
    while( k >= 2 && ccw( ch[k-2] , ch[k-1], ps[i] ) <= 0 ) --k;  
  for(int i= N-2, t = k+1; i >= 0; ch[k++] = ps[i--] )
    while( k >= t && ccw( ch[k-2] , ch[k-1] , ps[i] ) <= 0 ) --k;
  ch.resize(k-1);
  return ch;
}

// 凸包の直径
double convexDiamiter(vector<P> ps){
  int N = (int)ps.size();
  int i = 0, j = 0;
  for (int k = 1; k < N; k++) {
    if (imag(ps[k]) > imag(ps[i])) i = k;
    if (imag(ps[k]) < imag(ps[j])) j = k;
  }
  int si = i, sj = j;
  double max_dist = norm(ps[i] - ps[j]);
  do {
    if (cross(ps[(i+1)%N] - ps[i], ps[(j+1)%N] - ps[j]) >= 0) j = (j+1) % N;
    else i = (i+1) % N;
    if (norm(ps[i] - ps[j]) > max_dist) {
      max_dist = norm(ps[i] - ps[j]);
    }
  } while( si != i || sj != j );
  return sqrt(max_dist);
}
