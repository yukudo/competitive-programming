package ds.bit;

/**
 * 内部的には 1-based であるが、利用するときには 0-based
 * [idx, ∞] の範囲の最大値を返すBIT
 */
public class BITMAX {
	int n;
	int[] vs;
	public BITMAX(int n) {
		this.n = n;
		vs = new int[n+1];
	}

	/** [idx, ∞] の範囲の最大値を val で更新しようと試みる */
	public void update(int idx, int val) {
		for (int x = idx + 1; x <= n; x += x & -x) vs[x] = Math.max(vs[x], val);
	}

	/** [idx, ∞] の範囲の最大値を取得 */
	public int get(int idx) {
		int max = 0;
		for (int x = idx + 1; x > 0; x -= x & -x) max = Math.max(max, vs[x]);
		return max;
	}
	
}
