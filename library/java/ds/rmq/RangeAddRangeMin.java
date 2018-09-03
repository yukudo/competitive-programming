package ds.rmq;

import static java.lang.Math.*;

/**
 * 区間へのaddと、区間のmin
 */
public class RangeAddRangeMin {

	final static int INF = 1001001001;
	int n;
	long[] segMin;
	long[] segAdd;

	RangeAddRangeMin(int n) {
		this.n = n;
		int size = n <= 1 ? 1 : (Integer.highestOneBit(n - 1) << 2);
		segMin = new long[size];
		segAdd = new long[size];
	}

	/**
	 * 区間[a, b)に値xを加算する。
	 */
	void add(int a, int b, int x) {
		add(a, b, x, 0, 0, n);
	}
	private void add(int a, int b, int x, int k, int l, int r)
	{
		// ノード番号 k が、範囲 [l,r)。
		if (r <= a || b <= l) return; //もし交差しない区間であれば終える.
		if (a <= l && r <= b){ //もし今みている区間[l, r)が[a, b)に完全に内包されていれば
			segAdd[k] += x;  //区間[l, r)にkを加算する.
			while (k > 0){
				//親の区間の最小値は, 子の区間の最小値 + 自分に一様に加算されている値 である.一様に加算される値は更新しなくて良い.
				k = (k - 1) / 2;
				segMin[k] = min(segMin[k * 2 + 1] + segAdd[k * 2 + 1],
								segMin[k * 2 + 2] + segAdd[k * 2 + 2]);
			}
			return;
		}
		add(a, b, x, k * 2 + 1, l, (l + r) / 2);
		add(a, b, x, k * 2 + 2, (l + r) / 2, r);
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
		if (a <= l && r <= b) return (segMin[k] + segAdd[k]); //完全に内包されていれば,その区間の最小値を返す.
		long left = getMin(a, b, k * 2 + 1, l, (l + r) / 2); //子の区間の最小値を求める.
		long right = getMin(a, b, k * 2 + 2, (l + r) / 2, r); //子の区間の最小値を求める
		return min(left, right) + segAdd[k]; //親の区間の最小値は, 子の区間の最小値 + 自分に一様に加算されている値 である (大切なので2回書きました!!)
	}
}
