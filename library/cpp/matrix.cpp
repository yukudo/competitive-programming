#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define REP(i,n) for(int i=0,_n=(int)(n);i<_n;++i)
template<class T>bool chmin(T&a,const T&b){return a>b?(a=b,true):false;}
template<class T>bool chmax(T&a,const T&b){return a<b?(a=b,true):false;}

const ll MOD = ((ll)1e9)+7;

#define SZ(v) ((int)(v).size())
typedef vector<ll> Array;
typedef vector<Array> Matrix;

Matrix zero(int N){ return Matrix(N, Array(N)); }

Matrix identity(int N) {
  Matrix A = zero(N);
  REP(i, N) A[i][i] = 1;
  return A;
}

Matrix add(const Matrix &A, const Matrix& B){
  const int N = SZ(A);
  const int M = SZ(A[0]);
  Matrix C(N, Array(M));
  REP(i, N) REP(j, M) {
    C[i][j] += A[i][j] + B[i][j];
    if (C[i][j] >= MOD) C[i][j] %= MOD;
  }
  return C;
}

Array mul(const Matrix &A, const Array &x){
  const int N = SZ(A);
  const int M = SZ(A[0]);
  Array y(N);
  REP(i, N) REP(j, M)
    y[i] += A[i][j] * x[j];
  return y;
}

// A:[N,P] * B:[P,M] = C:[N,M]
Matrix mul(const Matrix &A, const Matrix& B) {
  const int N = SZ(A);
  const int P = SZ(A[0]);
  const int M = SZ(B[0]);
  Matrix C(N, Array(M));
  REP(i, N) REP(j, M) REP(k, P) {
    C[i][j] += A[i][k] * B[k][j];
    if (C[i][j] >= MOD) C[i][j] %= MOD;
  }
  return C;
}

// O ( n^3 log e )
// Matrix pow(const Matrix& A, ll e) {
//   return e == 0 ? identity(SZ(A)) :
//     e % 2 == 0 ? pow( mul(A,A) , e/2 ) : mul(A, pow(A,e-1));
// }
Matrix pow(Matrix A, ll b) {
  Matrix C = identity(SZ(A));
  while (b > 0) {
    if ((b & 1) == 1) C = mul(C, A);
    A = mul(A, A);
    b >>= 1;
  }
  return C;
}

// 0 + A + A^2 + ... + A^k
Matrix powsum(Matrix A, ll k) {
  if (k == 0) {
    return zero(SZ(A));
  } else if (k % 2 == 0) {
    Matrix P = powsum(A, k / 2);
    return add(P, mul(P, pow(A, k / 2)));
  } else if (k % 2 == 1) {
    return add(A, mul(A, powsum(A, k - 1)));
  }
}


void print(const Matrix& A){
  REP(i, SZ(A)){
    REP(j, SZ(A[0])){
      cout << A[i][j] << " ";
    }
    cout << endl;
  }
  cout << "---------------------" << endl;
}

//-===================================
// ここから下は double でやってください
//-===================================

const double EPS = 1e-10;


// O ( n^3 )
// by Gauss-Jordan elimination
// ( without errer handling )
Matrix inverse(Matrix A){
  int n = SZ(A);
  Matrix B = identity(n);
  REP(i, n) {
    int pivot = i;
    for(int j = i + 1; j < n; j++) if( abs(A[j][i]) > abs(A[pivot][i]) ) pivot = j;
    swap(A[pivot],A[i]);
    swap(B[pivot],B[i]);
    double div = A[i][i];
    if( abs( A[i][i] ) <= EPS ){
      cerr << "Matrix inverse(Matrix) failed" << endl;
      exit(1);
    }
    REP(j, n){
      A[i][j] /= div;
      B[i][j] /= div;
    }
    REP(r, n) {
      if( r == i )continue;
      double dif = A[r][i];
      REP(j, n) {
        A[r][j] -= dif * A[i][j];
        B[r][j] -= dif * B[i][j];
      }
    }
  }
  //  puts("A");print(A);
  return B;
}

// O( n^3 )
double det(Matrix A) {
  const int n = SZ(A);
  double D = 1;
  REP(i, n) {
    int pivot = i;
    for(int j = i + 1; i < n; i++)
      if (abs(A[j][i]) > abs(A[pivot][i])) pivot = j;
    swap(A[pivot], A[i]);
    D *= A[i][i] * (i != pivot ? -1 : 1);
    if (abs(A[i][i]) < EPS) break;
    for(int j = i + 1; i < n; i++)
      for(int k = n-1; k >= i; --k)
        A[j][k] -= A[i][k] * A[j][i] / A[i][i];
  }
  return D;
}

int rank(Matrix A) {
  const int n = SZ(A), m = SZ(A[0]);
  int r = 0;
  for (int i = 0; r < n && i < m; ++i) {
    int pivot = r;
    for (int j = r+1; j < n; ++j)
      if (abs(A[j][i]) > abs(A[pivot][i])) pivot = j;
    swap(A[pivot], A[r]);
    if (abs(A[r][i]) < EPS) continue;
    for (int k = m-1; k >= i; --k)
      A[r][k] /= A[r][i];
    for(int j = r + 1; j < n; j++)
      for(int k = i; k < m; k++)
        A[j][k] -= A[r][k] * A[j][i];
    ++r;
  }
  return r;
}

class not_regular{};
// Solve Ax = b
// O(n^3). row reduction
// 正方行列以外で動くのを確認していないし、解なしと解が無限個の区別もできない。
Array SolveLinerEquation(Matrix A, Array b){
  int N = SZ(A);
  int M = SZ(A[0]);
  REP(i, N) {
    // 部分pivot選択
    int pivot = i;
    for(int r = i + 1; r < N; r++)
      if( abs(A[r][i] > abs(A[pivot][i]) ) ) pivot = r;
    swap(A[pivot], A[i]);
    swap(b[pivot], b[i]);

    if( abs(A[i][i]) < EPS ) {
      // Aは非正則で、方程式の解は一意に定まらない。
      throw 1;
    }

    double d = 1 / A[i][i];
    for(int j = i; j < M; j++)
      A[i][j] *= d;
    b[i] *= d;

    REP(r, N) {
      if( r == i ) continue;
      double dif = A[r][i];
      REP(j, N) A[r][j] -= dif * A[i][j];
      b[r] -= dif * b[i];
    }
  }
  return b;
}

int main(){
  try{
    Matrix A;
    Array b;
    Array x = SolveLinerEquation(A,b);
  }catch (int e){
    cout << e << endl;
  }
}
