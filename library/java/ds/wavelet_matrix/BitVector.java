package ds.wavelet_matrix;


/**
 * ビット列に対して、以下の操作を O(1) で行う.前処理にO(n).
 * set()でビットを立てて、build()を呼び出してから、以下のクエリが使える．
 * - rank(k, x) : 位置 k までにビット x がいくつあるか.
 * - select(n, x) : n 個目の x の位置 + 1 はどこか（+1するのはrankとの対象性のため）.
 * 
 * select() は rank() の逆. すなわち rank(pos) == n となる最小の pos が select(n) である.
 */
public class BitVector {
	int[] blocks;
	int[] acc;
	public BitVector(int length) {
		blocks = new int[(length + 31) / 32];
	}
	public void set(int i) {
		blocks[i >> 5] |= 1 << (i & 31);
	}
	public void build() {
		acc = new int[blocks.length + 1]; // build() し忘れると nullpo するようにここで初期化
		for (int i = 0; i < blocks.length; i++) acc[i+1] = acc[i] + Integer.bitCount(blocks[i]);
	}
	public boolean access(int i) {
		return (blocks[i >> 5] & (1 << (i & 31))) != 0;
	}
	
	/** [0,pos)の 1 の個数 */
	private int rank(int pos) {
		int bi = pos >> 5;
		return  bi < blocks.length ?
				acc[bi] +Integer.bitCount(blocks[bi] & (1 << (pos & 31)) - 1) :
				acc[acc.length - 1];
	}
	/** [0,pos)の b の個数 */
	public int rank(int pos, boolean b) { return b ? rank(pos) : pos - rank(pos); }
	/** [left, right) の b の個数 */
	public int rank(int left, int right, boolean b) { return rank(right, b) - rank(left, b); }

	/**
	 * n番目の1の場所+1はどこか.
	 * 存在しないときは size より大きい数を何か返す.
	 * rank()の逆. すなわち rank(pos) == n となる最小の pos が select(n) である.
	 * 
	 * @param n (1-based)
	 */
	public int select(int n, boolean b) {
		if (n <= 0) return blocks.length * 32 + 1;
		int m = 0;
		for (int o = Integer.highestOneBit(blocks.length * 32); o > 0; o >>= 1) {
			if (rank(m + o, b) < n) m += o;
		}
		return m + 1;
	}

	@Override
	public String toString() {
		char[] buf = new char[blocks.length * 32];
		for (int i = 0; i < blocks.length * 32; i++)
			buf[i] = access(i) ? '1' : '0';
		return new String(buf);
	}

}
