package ds.persistent;

import java.util.Arrays;

/**
 * 内部を永続配列にしただけの UnionFind
 * あと10倍ぐらい速くないと使えなそう
 **/
public class PersistentUnionFind {

	private Node data;

	/** コンストラクタ */
	public PersistentUnionFind() {
		data = new Node();
	}
	public PersistentUnionFind(Node node) {
		data = node;
	}

	public int root(int x) {
		int res = x, nx = -1;
		while ((nx = get(res)) >= 0) res = nx;
		while (x != res) {
			int tmp = get(x);
			data = set(x, res);
			x = tmp;
		}
		return res;
	}
	
	public PersistentUnionFind link(int x, int y) {
		x = root(x);
		y = root(y);
		if (x != y) {
			int dy = get(y);
			int dx = get(x);
			if (dy > dx) {
				int t = dy; dy = dx; dx = t;
				t = y; y = x; x = t;
			}
			PersistentUnionFind im = new PersistentUnionFind(set(y, dy + dx));
			return new PersistentUnionFind(im.set(x, y));
		} else {
			Node newNode = new Node(data.val);
			newNode.ch[0] = data.ch[0];
			newNode.ch[1] = data.ch[1];
			return new PersistentUnionFind(newNode);
		}
	}

	// 0-indexed
	private int get(int index) {
		return data.get(index + 1);
	}

	private Node set(int index, int val) {
		index++;
		int order = 1;
		while (index > 1) {
			order = (order << 1) + (index & 1);
			index >>= 1;
		}
		Node newNode = data.set(order, val);
		return newNode;
	}

	class Node {
		static final int defaultValue = -1;
		Node[] ch = new Node[2];
		public int val;
		public Node() { this.val = defaultValue; }
		public Node(int val) { this.val = val; }
		int get(int index) {
			int order = 1;
			while (index > 1) {
				order = (order << 1) + (index & 1);
				index >>= 1;
			}
			Node node = this;
			for (; order > 1;) {
				node = node.ch[order & 1];
				order >>= 1;
				if (node == null) return defaultValue;
			}
			return node.val;
		}

		Node set(int order, int val) {
			Node alter = new Node(this.val);
			if (order == 1) {
				alter.val = val;
				alter.ch[0] = this.ch[0];
				alter.ch[1] = this.ch[1];
				return alter;
			}
			int f = order & 1;
			Node next = ch[f];
			if (next == null) next = new Node();
			alter.ch[f] = next.set(order >> 1, val);
			alter.ch[1-f] = this.ch[1-f];
			return alter;
		}
	}

	/**
	 * 動作確認用メイン
	 */
	public static void main(String[] args) {
		long start = System.currentTimeMillis();
		
		{
			PersistentUnionFind[] a = new PersistentUnionFind[10];
			a[0] = new PersistentUnionFind();
			a[1] = a[0].link(0, 1);
			a[2] = a[1].link(2, 3);
			a[3] = a[2].link(4, 5);
			a[4] = a[3].link(6, 7);
			a[5] = a[4].link(0, 3);
			a[6] = a[5].link(6, 7);
			a[7] = a[6].link(0, 1);
			a[8] = a[7].link(1, 0);
			a[9] = a[8].link(0, 7);
			debug(a);
		}
		long end = System.currentTimeMillis();
		tr(end - start + "ms");
	}
	
	static void debug(PersistentUnionFind[] a) {
		for (int i = 0; i < a.length; i++) {
			System.out.print(i + ":   ");
			if (a[i] == null) System.out.print("null");
			else
			for (int j = 0; j < 10; j++) System.out.print(a[i].root(j) + " ");
			System.out.println();
		}
	}

	public static void tr(Object...o) {
		System.err.println(Arrays.deepToString(o));
	}
}
