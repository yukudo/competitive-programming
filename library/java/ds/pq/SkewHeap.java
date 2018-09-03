package ds.pq;


/**
 * meldable heap
 * http://hos.ac/blog/#blog0001
 */
public class SkewHeap {
	SkewHeap l, r;
	long val;
	public SkewHeap(long val) {
		this.val = val;
	}
	static SkewHeap add(SkewHeap x, long val) { return meld(x, new SkewHeap(val)); }
	static SkewHeap pop(SkewHeap x) { return meld(x.l, x.r); }
	static SkewHeap meld(SkewHeap a, SkewHeap b) {
		if (a == null) return b;
		if (b == null) return a;
		if (a.val > b.val) { SkewHeap tmp = a;a = b;b = tmp; }
		a.r = meld(a.r, b);
		{ SkewHeap tmp = a.l;a.l = a.r;a.r = tmp; }
		return a;
	}
}
