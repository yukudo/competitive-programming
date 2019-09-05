#include <complex>
using namespace std;

typedef long double D;
const D PI = acos(-1.0);
const D EPS = 1e-10;
class P { public:
  D x, y;
  P(D x=0, D y=0) : x(x), y(y) {}

  P& operator+=(const P& o) { x += o.x; y += o.y; return *this; }
  P& operator-=(const P& o) { x -= o.x; y -= o.y; return *this; }
  P& operator*=(const P& o) { return *this = {x*o.x - y*o.y, x*o.y + y*o.x}; }
  P& operator*=(const D& r) { x *= r; y *= r; return *this; }
  P& operator/=(const D& r) { x /= r; y /= r; return *this; }
  P operator-() const { return {-x, -y}; }

  D norm() const { return x*x + y*y; }
  D abs() const { return sqrt(norm()); }
  D arg() const { return atan2(y, x); }
  bool isZero() const { return std::abs(x) < EPS && std::abs(y) < EPS; }
  /** 象限 */
  int orth() const { return y >= 0 ? (x >= 0 ? 1 : 2) : (x < 0 ? 3 : 4); }
  static P polar(const D& rho, const D& theta = 0) { return {rho * cos(theta), rho * sin(theta)}; }
};
std::ostream &operator<<(std::ostream &os, P const &p) { return os << "(" << p.x << ", " << p.y << ")"; }
std::istream &operator>>(std::istream &is, P &p) { D a, b; is >> a >> b; p = P(a, b); return is; }
P operator+(const P& p, const P& q) { return P(p) += q; }
P operator-(const P& p, const P& q) { return P(p) -= q; }
P operator*(const P& p, const P& q) { return P(p) *= q; }
P operator*(const P& p, const D& r) { return P(p) *= r; }
P operator/(const P& p, const D& r) { return P(p) /= r; }
P operator*(const D& r, const P& p) { return P(p) *= r; }
P operator/(const D& r, const P& p) { return P(p) /= r; }
D crs(const P& a, const P& b){ return a.x*b.y - a.y*b.x; }
D dot(const P& a, const P& b){ return a.x*b.x + a.y*b.y; }
int signum(D x) {return x > EPS ? +1 : x < -EPS ? -1 : 0;}
// 辞書順ソート
bool operator<(const P& a, const P& b) {
  if (a.x != b.x) return a.x < b.x;
  return a.y < b.y;
}
// // 偏角ソート
// bool operator<(const P& a, const P& b) {
//   // atan2を使う方法。誤差に注意
//   // return a.arg() < b.arg();

//   // cosを使う方法。(0,0)の扱いに注意
//   if (a.isZero() != b.isZero()) return a.isZero() > b.isZero();
//   if (a.orth() != b.orth()) return a.orth() < b.orth();
//   return crs(a, b) > 0;
// }
/** ベクトルpをベクトルbに射影したベクトル */
P proj(const P& p, const P& b) {
  P t = b * dot(p, b);
  return t / b.norm();
}
/** 点pから直線abに引いた垂線の足となる点 */
P footOfLP(const P& a, const P& b, const P& p) {
  return a + proj(p-a, b-a);
}
/** 直線abを挟んで点pと対称な点 */
P reflection(const P&a, const P&b, const P& p) {
  return 2 * footOfLP(a, b, p) - p;
}
int ccw(const P& a, P b, P c) {
  // return signum(crs(b - a, c - a));
  b -= a; c -= a;
  if (crs(b, c) > 0)       return +1;       // counter clockwise
  if (crs(b, c) < 0)       return -1;       // clockwise
  if (dot(b, c) < 0)       return +2;       // c--a--b on line
  if (b.norm() < c.norm()) return -2;       // a--b--c on line
  return 0;
}
/** 2直線の直行判定 : a⊥b <=> dot(a, b) = 0 */
bool isOrthogonal(const P& a1, const P& a2, const P& b1, const P& b2) {
  return abs(dot(a1-a2, b1-b2)) < EPS;
}
/** 2直線の平行判定 : a//b <=> crs(a, b) = 0 */
bool isParallel(const P& a1, const P& a2, const P& b1, const P& b2) {
  return abs(crs(a1-a2, b1-b2)) < EPS;
}
/** 点cが直線ab上にあるか */
bool isIntersectLP(const P& a, const P& b, const P& c){
  return abs(crs(b-a, c-a)) < EPS;
}
/** 点cが線分ab上にあるか : |a-c| + |c-b| <= |a-b| なら線分上 */
bool isIntersectSP(const P& a, const P& b, const P& c){
  return ((a-c).abs() + (c-b).abs() < (a-b).abs() + EPS);
}
/** 直線aと直線bの交差判定 */
bool isIntersectLL(const P& a, const P& b, const P& c, const P& d){
  return abs(crs(b-a, d-c)) > EPS || // non-parallel
         abs(crs(b-a, c-a)) < EPS;   // same line
}
/** 直線abと線分cdの交差判定 */
bool isIntersectLS(const P& a, const P& b, const P& c, const P& d){
  return crs(b-a, c-a) *      //c is left of ab
         crs(b-a, d-a) < EPS; //d is right of ab
}
/** 線分と線分の交差判定。端点が重なってもtrue */
bool isIntersectSS(const P& a1, const P& a2, const P& b1, const P& b2){
  return ccw(a1,a2,b1) * ccw(a1,a2,b2) <= 0 &&
         ccw(b1,b2,a1) * ccw(b1,b2,a2) <= 0;
}

P intersectionLL(const P& a1, const P& a2, const P& b1, const P& b2){
  P a = a2 - a1; P b = b2 - b1;
  return a1 + a * crs(b, b1-a1) / crs(b, a);
}
D distSP(const P& a, const P& b, const P& c) {
  if (dot(b-a, c-a) < EPS) return (c-a).abs(); // c a--b
  if (dot(a-b, c-b) < EPS) return (c-b).abs(); // a--b c
  return abs(crs(b-a, c-a)) / (b-a).abs();
}
D distSS(const P& a1, const P& a2, const P& b1, const P& b2){
  if (isIntersectSS(a1,a2,b1,b2)) return 0.0;
  return min(min(distSP(a1, a2, b1), distSP(a1, a2, b2)),
             min(distSP(b1, b2, a1), distSP(b1, b2, a2)));
}
double area(const vector<P> &v) {
  double ret = 0.0;
  REP(i, v.size()) ret += crs(v[i], v[(i+1) % v.size()]);
  return abs(ret / 2.0);
}
bool isConvex(const vector<P> &ps) {
  int N = ps.size();
  int m = 0;
  REP(i, N) {
    int dir = ccw(ps[i], ps[(i+1)%N], ps[(i+2)%N]);
    if (dir == 1) m |= 1;
    if (dir == -1) m |= 2;
  }
  return m != 3;
}

// 凸包
/** 多角形と点の内外判定。点pをx軸方向に無限に伸ばした半直線と多角形の辺が交差する回数が、奇数ならば内、偶数ならば外。*/
enum { OUT, IN, ON };
int contains(const vector<P>& ps, const P& p) {
  bool in = false;
  int N = ps.size();
  REP(i, N) {
    P a = ps[i] - p, b = ps[(i+1)%N] - p;
    if (a.y > b.y) swap(a, b);
    if (a.y <= 0 && 0 < b.y)
      if (crs(a, b) < 0) in = !in;
    if (crs(a, b) == 0 && dot(a, b) <= 0) return ON;
  }
  return in ? IN : OUT;
}

// 凸包上の点も拾う場合は2箇所を <= 0 から == -1 に変える http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A
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
D convexDiamiter(vector<P> ps){
  int N = (int)ps.size();
  int i = 0, j = 0;
  for (int k = 1; k < N; k++) {
    if (imag(ps[k]) > imag(ps[i])) i = k;
    if (imag(ps[k]) < imag(ps[j])) j = k;
  }
  int si = i, sj = j;
  D max_dist = norm(ps[i] - ps[j]);
  do {
    if (crs(ps[(i+1)%N] - ps[i], ps[(j+1)%N] - ps[j]) >= 0) j = (j+1) % N;
    else i = (i+1) % N;
    if (norm(ps[i] - ps[j]) > max_dist) {
      max_dist = norm(ps[i] - ps[j]);
    }
  } while( si != i || sj != j );
  return sqrt(max_dist);
}
