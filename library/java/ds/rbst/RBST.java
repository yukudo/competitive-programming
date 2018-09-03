package ds.rbst;

import java.util.Random;

/**
 *
 * RBST とは実装が軽くコンテスト向けの平衡二分木である。
 * かなりの種類の操作が O(nlogn) でできる。
 *
 * Treap から優先度を持たないようにし、
 * マージ時に確率的に根が選ばれるようにしたデータ構造である。
 *
 * なお、Treap とはノードが「キー」と「優先度」という２つの値を持ち、
 * キーについては「二分探索木の条件」（値の大きさが、 左の子 < 親 < 右の子）を満たし、
 * 優先度については「ヒープの条件」（値の大きさが、親 > 子）を満たすデータ構造である。
 *
 * merge-split ベースの実装
 *
 * AOJ1508
 */
class RBST {

	static final int INF = 1001001001;
	static Random random = new Xorshift();

	static class Xorshift extends Random {
		long x,y,z,w;

		public Xorshift() {
			setSeed(System.nanoTime());
		}

		public void setSeed(long seed) {
			x = seed;
			y = 362436069;
			z = 521288629;
			w = 88675123;
		}

		public long nextLong() {
			long t = (x ^ (x << 11));x = y;y = z;z = w;
			return (w = (w ^ (w >>> 19)) ^ (t ^ (t >>> 8)));
		}

		public int nextInt() {
			return (int) nextLong();
		}

		public int nextInt(int n) {
			int x = (int) (nextLong() % n);
			return x >= 0 ? x : x + n;
		}

		// [a, b)
		public int nextInt(int a, int b) {
			return nextInt(b - a) + a;
		}
	}

	static class Node {
		Node l, r;
		int val;
		int size; // subtree size
		int min;
	}

	static final int POOL_SIZE = 200000 + 100;
	static int sp = 0;
	static Node[] pool;
	static {
		pool = new Node[POOL_SIZE];
		for (int i = 0; i < pool.length; i++) pool[i] = new Node();
	}
	static Node newNode(int val) {
		Node t = pool[sp++];
		t.l = t.r = null;
		t.size = 1;
		t.val = val;
		t.min = val;
		return t;
	}
	private static final Node[] EP = new Node[2];
	static int size(Node t) { return t == null ? 0 : t.size; }
	static int min(Node t) { return t == null ? INF : t.min; }

	static Node update(Node t) {
		t.size = size(t.l) + size(t.r) + 1;
		t.min = Math.min(Math.min(min(t.l), min(t.r)), t.val);
		return t;
	}
	static Node merge(Node t1, Node t2) {
		if (t1 == null) return t2;
		if (t2 == null) return t1;
		if (random.nextInt(t1.size + t2.size) < t1.size) {
			t1.r = merge(t1.r, t2);
			return update(t1);
		} else {
			t2.l = merge(t1, t2.l);
			return update(t2);
		}
	}

	// [a, b)
	static int min(Node t, int a, int b) {
		if (t == null) return INF;
		if (a <= 0 && size(t) <= b) {
			return t.min;
		}
		int res = INF;
		if (a < size(t.l)) {
			int x = min(t.l, a, b);
			if (res > x) res = x;
		}
		if (a <= size(t.l) && size(t.l) < b) {
			if (res > t.val) res = t.val;
		}
		if (b >= size(t.l) + 1) {
			int x = min(t.r, a - size(t.l) - 1, b - size(t.l) - 1);
			if (res > x) res = x;
		}
		return res;
	}

	static Node[] split(Node t, int k) { // [0, k), [k, n)
		if (t == null) return EP;
		if (k <= size(t.l)) {
			Node[] s = split(t.l, k);
			t.l = s[1];
			return new Node[] {s[0], update(t)};
		} else {
			Node[] s = split(t.r, k - size(t.l) - 1);
			t.r = s[0];
			return new Node[] {update(t), s[1]};
		}
	}
	static Node insert(Node t, int k, int val) {
		Node[] s = split(t, k);
		return merge(merge(s[0], newNode(val)), s[1]);
	}
	// [0, n) -> [0, k) + [k+1, n)
	static Node erase(Node t, int k) {
		Node[] s = split(t, k);
		Node[] s2 = split(s[1], 1);
		return merge(s[0], s2[1]);
	}
	static void changeVal(Node t, int k, int val) {
		if (t == null) return;
		if (size(t.l) > k)
			changeVal(t.l, k, val);
		else if (size(t.l) == k)
			t.val = val;
		else
			changeVal(t.r, k - size(t.l) - 1, val);
		update(t);
	}
	static Node rot(Node t, int a, int b) {
		Node[] r1 = split(t, a);
		Node[] r2 = split(r1[1], b - a - 1);
		Node[] r3 = split(r2[1], 1);
		return merge(merge(r1[0], r3[0]), merge(r2[0], r3[1]));
	}
}
