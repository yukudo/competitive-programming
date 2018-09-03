package ds.rmq;

import static java.lang.Math.*;

/**
 * 区間へのaddと区間のsum
 */
public class RangeAddRangeSum {
	int n;
	long[] all;
	long[] part;

	RangeAddRangeSum(int n) {
		this.n = n;
		int size = n == 1 ? 1 : (Integer.highestOneBit(n - 1) << 2);
		all = new long[size];
		part = new long[size];
	}

	/**
	 * 区間[a, b)に値xを加算する。
	 */
	void add(int a, int b, int x) {
		add(a, b, x, 0, 0, n);
	}
	private void add(int a, int b, int x, int k, int l, int r)
	{
		if (b <= l || r <= a){ //[a, b)と[l, r)が全く交差しない場合

		} else if (a <= l && r <= b) { //[l, r)が[a, b)に完全に内包されていれば
			all[k] += x; //[l, r)の全ての区間が持つ値としてxを足す.
		} else { //[l, r)と[a, b)が交差していれば
			part[k] += (min(b, r) - max(a, l)) * (long)x;  //交差している分の値を, 部分的な和を持つノードに加算する.
			add(a, b, x, k * 2 + 1, l, (l + r) / 2);
			add(a, b, x, k * 2 + 2, (l + r) / 2, r);
		}
	}

	/**
	 * 区間[a, b)の合計
	 */
	long getSum(int a, int b) {
		return getSum(a, b, 0, 0, n);
	}

	private long getSum(int a, int b, int k, int l, int r)
	{
		if (b <= l || r <= a){ //[a, b)と[l, r)が全く交差しない場合
			return 0;
		}
		else if (a <= l && r <= b){ //完全に内包されていれば
			return (all[k] * (r - l) + part[k]);
		}
		else { //[l, r)と[a, b)が交差していれば
			long res;
			res = (min(b, r) - max(a, l)) * all[k]; //そのノードの全ての要素が持つ値のうち, [a, b)に属すものの分だけを加算する.
			res += getSum(a, b, k * 2 + 1, l, (l + r) / 2);
			res += getSum(a, b, k * 2 + 2, (l + r) / 2, r);
			return (res);
		}
	}
}
