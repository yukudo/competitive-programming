package ds.rmq;

import java.util.Arrays;

/**
 * 点のupdateと区間のmin
 * Segment Tree による実装
 */
public class PointUpdateRangeMin {
	static final int INF = 1001001001;
	int n;
	long[] segMin;

	PointUpdateRangeMin(int n) {
		this.n = n;
		int size = n <= 1 ? 1 : (Integer.highestOneBit(n - 1) << 2);
		segMin = new long[size];
		fill(INF);
	}

	void fill(long val) {
		Arrays.fill(segMin, val);
	}

	void update(int a, long x) {
		update(a, x, 0, 0, n);
	}
	private void update(int a, long x, int k, int l, int r)
	{
		// ノード番号 k が、範囲 [l,r)。
		if (l <= a && a < r) {
			segMin[k] = Math.min(segMin[k], x);
			if (r - l >= 2) {
				update(a, x, k * 2 + 1, l, (l + r) / 2);
				update(a, x, k * 2 + 2, (l + r) / 2, r);
			}
		}
	}

	/**
	 * 区間[a, b) の最小値を返す。
	 */
	long getMin(int a, int b) {
		return getMin(a, b, 0, 0, n);
	}

	private long getMin(int a, int b, int k, int l, int r)
	{
		// ノード番号 k が、範囲 [l,r)。
		if (r <= a || b <= l) return INF;
		if (a <= l && r <= b) return (segMin[k]);
		long left = getMin(a, b, k * 2 + 1, l, (l + r) / 2); //子の区間の最小値を求める.
		long right = getMin(a, b, k * 2 + 2, (l + r) / 2, r); //子の区間の最小値を求める
		return Math.min(left, right);
	}
}
