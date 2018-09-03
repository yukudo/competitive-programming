package ds.bit;

import java.util.Arrays;

/**
 * 内部的には 1-based であるが、利用するときには 0-based
 * 
 * BITを2本使って範囲addを実現する方法はテストケースに書いた。
 */
public class BIT {
	int n;
	long[] vs;
	public BIT(int n) {
		this.n = n;
		vs = new long[n+1];
	}
	/** v[idx]の値を+valする*/
	void add(int idx, long  val) {
		for (int x = idx + 1; x <= n; x += x & -x) vs[x] += val;
	}
	/** 全体をa[]で初期化する。ひとつずつaddしていくよりも高速。 */
	void load(int[] a) {
		Arrays.fill(vs, 0);
		for (int i = 0; i < a.length; i++) vs[i+1] = a[i];
		for (int x = 1; x < n; x++) if (x + (x & -x) < vs.length) vs[x + (x & -x)] += vs[x];
	}
	/** 全体をvalで埋める */
	void fill(int val) {
		for (int x = 1; x <= n; x++) vs[x] = (x & -x) * val;
	}
	/** [0,idx]の和 */
	long range(int idx) {
		long sum = 0;
		for (int x = idx + 1; x > 0; x -= x & -x) sum += vs[x];
		return sum;
	}
	/** [a,b]の和 */
	long range(int a, int b) {
		return range(b) - range(a - 1);
	}
	/** range(x) >= w となる最小の x を求める。range(x)は単調増加であること（すなわちv[idx]が非負であること）。 
	 * 全てを足してもwに達しない場合はsize(＝有効な添字の最大値+1)が返される。*/
	int find(long w) {
		int x = 0;
		for (int k = Integer.highestOneBit(n); k > 0; k >>= 1)
			if (x + k <= n && vs[x + k] < w) {
				w -= vs[x + k];
				x += k;
			}
		return x;
	}

	String dump(int m) {
		StringBuilder sb = new StringBuilder();
		sb.append("[");
		for (int i = 0; i < m; i++) {
			sb.append(range(i, i)).append(", ");
		}
		sb.append("]");
		return sb.toString();
	}

}
