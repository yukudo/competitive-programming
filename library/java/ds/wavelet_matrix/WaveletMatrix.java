package ds.wavelet_matrix;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

/**
 * ある範囲内に特定のデータがいくつあるかを定数時間でクエリできる。
 * O(1)は、値のビット数なので値の範囲が0<=a[i]<=10^9ならO(log32)かかるという意味。
 * BitVectorの実装をサボっているため余計にO(logn)ぐらいかかってる。
 * - 初期化 O(nlogn)ぐらい
 * - クエリO(1)
 * - 値は非負整数
 * - 値の更新はできない
 * 
 * @see http://d.hatena.ne.jp/takeda25/20130303/1362301095
 * @see http://ja.scribd.com/doc/102636443/Wavelet-Matrix
 * verified POJ2014 K-th Number
 */
public class WaveletMatrix {

	static final int LEVEL = 32; // 例えば数の範囲が 10^6 なら LEVEL=20 にすると若干高速.
	private int[] a; // build()の過程で更新され、bit reversed radix sort 後の配列が保持される.
	private BitVector[] bvs = new BitVector[LEVEL];
	private int[] zeros = new int[LEVEL]; // 各段階での 0 の個数
	private Map<Integer, Integer> lowerBound = new HashMap<Integer, Integer>(); // 更新後の a[] でのそれぞれの数の開始位置

	public WaveletMatrix(int[] a) {
		this.a = a.clone();
		build();
	}

	private void build() {
		int[] tmp = new int[a.length];
		for (int bit = LEVEL-1; bit >= 0; bit--) {
			BitVector bv = new BitVector(a.length);
			int zero = 0, one = 0;
			for (int i = 0; i < a.length; i++) {
				if ((a[i] >> bit & 1) == 1) {
					bv.set(i);
					tmp[one++] = a[i];
				} else {
					a[zero++] = a[i];
				}
			}
			for (int i = 0; i < one; i++) a[zero + i] = tmp[i];
			zeros[bit] = zero;
			bv.build();
			bvs[bit] = bv;
		}
		for (int i = 0; i < a.length; i++) if (i == 0 || a[i-1] != a[i]) lowerBound.put(a[i], i);
	}

	/**
	 * i番目の要素を返す.
	 * 元の配列は保持していないので BitVector から復元する.
	 */
	public int access(int i) {
		int res = 0;
		for (int bit = LEVEL-1; bit >= 0; bit--) {
			boolean b = bvs[bit].access(i);
			i = bvs[bit].rank(i, b) + (b ? zeros[bit] : 0);
			if (b) res |= (1 << bit);
		}
		return res;
	}

	/**
	 * [0, k) での値 x の出現回数.
	 */
	public int rank(int k, int x) {
		Integer first = lowerBound.get(x);
		if (first == null) return 0;
		for (int bit = LEVEL-1; bit >= 0; bit--) {
			boolean b = (x >> bit & 1) == 1;
			int l = bvs[bit].rank(k, b);
			k = l + (b ? zeros[bit] : 0);
		}
		return k - first;
	}

	/**
	 * n 個目の文字 x の位置 + 1 を返す.
	 * 存在しない場合は a.length より大きい数を返す.
	 * @param n (1-based)
	 */
	public int select(int n, int x) {
		Integer first = lowerBound.get(x);
		if (first == null) return a.length + 1;
		int pos = first + n;
		if (pos >= a.length || a[pos-1] != x) return a.length + 1;
		for (int bit = 0; bit < LEVEL; bit++) {
			boolean b = (x >> bit & 1) == 1;
			pos = bvs[bit].select(pos - (b ? zeros[bit] : 0), b);
		}
		return pos;
	}


	/**
	 * 範囲 [l, r) のなかで x より小さい, x と同じ, x より大きいものの個数を返す.
	 * @return { xより小さい, xと同じ, xより大きい }
	 */
	public int[] rankLessThan(int l, int r, int x) {
		int less = 0, greater = 0;
		for (int bit = LEVEL - 1; bit >= 0; bit--) {
			boolean b = (x >> bit & 1) == 1;
			int nl = bvs[bit].rank(l, b);
			int nr = bvs[bit].rank(r, b);
			if (b) {
				nl += zeros[bit];
				nr += zeros[bit];
				less += (r - l) - (nr - nl);
			} else {
				greater += (r - l) - (nr - nl);
			}
			l = nl;
			r = nr;
		}
		return new int[] { less, r - l, greater };
	}

	/**
	 * 範囲 [l, r) のなかで n 番目に小さい数を返す.
	 * @param n (1-based)
	 */
	public int quantileRange(int l, int r, int n) {
		int nl, nr;
		for (int bit = LEVEL - 1; bit >= 0; bit--) {
			int zl = bvs[bit].rank(l, false);
			int zr = bvs[bit].rank(r, false);
			int z = zr - zl;
			if (z < n) {
				nl = zeros[bit] + (l - zl);
				nr = zeros[bit] + (r - zr);
				n -= z;
			} else {
				nl = zl;
				nr = zr;
			}
			l = nl;
			r = nr;
		}
		return a[l];
	}

	@Override
	public String toString() {
		int[] buf = new int[a.length];
		for (int i = 0; i < a.length; i++) buf[i] = access(i);
		return Arrays.toString(buf);
	}
}
