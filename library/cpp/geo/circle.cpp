struct C : public P {
  D r;
  C() {}
  C(const P &p, D r):P(p),r(r){}
};

// 円cと点pの接点をvectorで返す
vector<P> contactCP(C c, P p){
  vector<P> ret;
  D dist2 = (p - c).norm();
  D r2 = c.r * c.r;
  if( abs( r2 - dist2 ) < EPS ){ // 点が円周上にある
    ret.push_back( p );
    return ret;
  }
  if( r2 > dist2 ){ //点が円の内部にある
    return ret;
  }
  P q1 = (p - c) * ( r2 / dist2 );
  P q2 = (p - c) * P(0, 1) * (c.r * sqrt(dist2 - r2) / dist2);
  ret.push_back(c + q1 + q2);
  ret.push_back(c + q1 - q2);
  return ret;
}

// 2円の共通接線
vector<P> contactCC(const C& c1, const C& c2){
  vector<P> res;
  if (abs(c1.r - c2.r) < EPS) { // 外接線が平行
    P dir = c2 - c1;
    dir = dir * c1.r / dir.abs() * P(0,1);
    res.push_back(c1 + dir);
    res.push_back(c2 + dir);
    res.push_back(c1 - dir);
    res.push_back(c2 - dir);
  } else {
    P p = (c1 * -c2.r + c2 * c1.r) / (c1.r - c2.r);
    vector<P> ps = contactCP(c1, p);
    vector<P> qs = contactCP(c2, p);
    for (int i = 0; i < (int)ps.size() && i < (int)qs.size(); i++) {
      res.push_back(ps[i]);
      res.push_back(qs[i]);
    }
  }
  //内接線
  P p = (c1 * c2.r + c2 * c1.r) / (c1.r + c2.r);
  vector<P> ps = contactCP(c1, p);
  vector<P> qs = contactCP(c2, p);
  for (int i = 0; i < (int)ps.size() && i < (int)qs.size(); i++) {
    res.push_back(ps[i]);
    res.push_back(qs[i]);
  }
  return res;
}

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

// 直線abと円cの交点をvectorで返す
vector<P> intersectionLC(const P& a, const P& b, const C& c){
  double dist = distLP(a,b,c);
  vector<P> ret;
  if( abs(dist - c.r) < EPS ) {
    ret.push_back( footOfLP(a,b,c) );
  } else if( dist < c.r ) {
    P m = footOfLP(a,b,c);
    P u = (b-a) / (b-a).abs();
    double t = sqrt( c.r * c.r - dist * dist );
    ret.push_back( m + t * u );
    ret.push_back( m - t * u );
  }
  return ret;
}
// 2円の交点
vector<P> intersectionCC(const C& c1, const C& c2) {
  vector<P> ret;
  D d = (c1 - c2).abs();
  P diff = (c2 - c1) / d;
  if( c1.r + c2.r < d - EPS ) {                        // 離れていて交点0

  } else if( d < EPS && abs(c1.r - c2.r) < EPS ) {     // 2円が重なる

  } else if( abs( c1.r + c2.r - d ) < EPS ) {          // 外側で1点で接する
    ret.push_back( c1 + diff * c1.r );
  } else if( abs( c1.r - c2.r ) > d + EPS ) {          // 内側に含む。交点0

  } else if( abs( abs( c1.r - c2.r ) - d ) < EPS) {    // 内側で1点で接する
    ret.push_back( c1 + diff * c1.r );
  } else {                                            // 2点で交わる
//     assert( d < c1.r + c2.r );
    D rc = (d*d + c1.r*c1.r - c2.r*c2.r) / (2*d);
    D rs = sqrt(c1.r*c1.r - rc*rc);

    ret.push_back( c1 + diff * P(rc, -rs) );
    ret.push_back( c1 + diff * P(rc, rs) );
  }
  return ret;
}
