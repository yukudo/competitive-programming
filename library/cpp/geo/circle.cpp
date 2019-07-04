#include <complex>

typedef long double D;
typedef complex<D> P;
const D PI = acos(-1.0);
const D EPS = 1e-10;

struct C : public P {
  D r;
  C() {}
  C(const P &p,D r):P(p),r(r){}
};

// 2円の共通部分の面積
D ccArea(const C& c1, const C& c2) {
  D d = abs(c1 - c2);
  if (c1.r + c2.r <= d + EPS) return 0;
  if (d <= abs(c1.r-c2.r) + EPS) {
      D r = min(c1.r, c2.r);
      return r*r*PI;
  }
  auto cut = [](D r1, D r2, D d) -> D {
    D ang = 2 * acos((d*d + r1*r1 - r2*r2) / (2*d*r1));
    return (ang - sin(ang)) * r1 * r1 * 0.5;
  };
  return cut(c1.r, c2.r, d) + cut(c2.r, c1.r, d);
}
