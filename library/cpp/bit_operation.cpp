// LSBのindex(1-based)を返す
unsigned int __builtin_ffs(unsigned int); 

// leading zero の個数を返す
unsigned int __builtin_clz(unsigned int); 

// trailing zero の個数を返す
unsigned int __builtin_ctz(unsigned int); 

// 1であるビットの数を数える。
unsigned int __builtin_popcount(unsigned int); 

// 1であるビットの数 % 2を返す
unsigned int __builtin_parity(unsigned int); 

それぞれにunsigned long long版もある。
unsigned long long __builtin_popcountll(unsigned long long);

// 最右ビットを落とす。
y = x&(x-1);

// x が 2^n かどうか
(x & (x-1)) == 0

// こちらは 2^n - 1の形 （000011111） かどうかの判定に使える。
x & (x + 1)

// 最右ビット(LSB)を抜き出す。
y = x&-x;
// unsignedでもOK
y = (n^(n-1))&n;

// 最右の 0 のビットだけ立てる  10100111 → 00001000
~x & (x + 1)

// 最上位ビット(MSB)を抜き出す
int highestOneBit(unsigned int i) {
    i |= (i >>  1);
    i |= (i >>  2);
    i |= (i >>  4);
    i |= (i >>  8);
    i |= (i >> 16);
    return i - (i >> 1);
}

// 右から見ていき1がでるまで0を1にする
y = x|(x-1);

// 非零部分集合を列挙する。
// 昇順
#define FOR_SUBSET(b, a) for(int b = (a)&-(a); b != 0; b = (((b|~(a))+1)&(a)))
// 降順
#define FOR_SUBSET(b, a) for(int b = a; b != 0; b = (b-1)&a)

// 問題の構造によっては、非部分集合を列挙せずとも、1が立ってるビット1つを0にしたやつらだけを考えればいいかもしれないよ。
 
// ビットコンビネーションを列挙する。
int next_combination(int p) {
    int lsb = p&-p;
    int rem = p+lsb;
    int rit = rem&~p;
    return rem|(((rit/lsb)>>1)-1);
}
// 8C4の列挙
int p = (1 << 4) - 1;
do {
  cout << bitset<16>(p) << endl;
} while( (p = next_combination(p)) < (1 << 8) );

// 立っているビットの数を数える
int popcount(int x){
        x = (x & 0x55555555) + ((x >> 1) & 0x55555555);
        x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
        x = (x & 0x0f0f0f0f) + ((x >> 4) & 0x0f0f0f0f);
        x = (x & 0x00ff00ff) + ((x >> 8) & 0x00ff00ff);
        x = (x & 0x0000ffff) + ((x >> 16) & 0x0000ffff);
        return x;
}
