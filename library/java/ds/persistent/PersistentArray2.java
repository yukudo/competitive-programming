package ds.persistent;

import java.util.Arrays;

// 中間ノードにも状態を持つ。 PersistentArray よりこっちのほうがいい。未検証。
public class PersistentArray2 {
	
	int defaultValue = -1;
	Node root;
	
	/**
	 * コンストラクタ
	 */
	public PersistentArray2() {
		root = new Node();
	}
	public PersistentArray2(Node node) {
		this.root = node;
	}
	// 0-indexed
	private int get(int index) {
		return root.get(index + 1);
	}

	private Node set(int index, int val) {
		index++;
		int order = 1;
		while (index > 1) {
			order = (order << 1) + (index & 1);
			index >>= 1;
		}
		Node newNode = root.set(order, val);
		return newNode;
	}

	class Node {
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
			PersistentArray2[] a = new PersistentArray2[11];
			a[0] = new PersistentArray2();
			for (int i = 1; i < 11; i++) {
				a[i] = new PersistentArray2(a[i-1].set(i-1, i));
				debug(a);
			}
		}
		
		{
			PersistentArray2[] a = new PersistentArray2[11];
			a[10] = new PersistentArray2();
			for (int i = 9; i >= 1; i--) {
				a[i] = new PersistentArray2(a[i+1].set(i-1, i));
				debug(a);
			}
		}
		{
		int MOD = 10007;
		int n = 200000;
		PersistentArray2 a = new PersistentArray2();
		int q = 200000;

		PersistentArray2 mid = null;
		for (int i = 0; i < q; i++) {
			a = new PersistentArray2(a.set(i, i));
			if (i == q / 2) mid = a;
		}

		a.debug(n);
		mid.debug(n);

		}
		
		long end = System.currentTimeMillis();
		tr(end - start + "ms");
	}
	
	static void debug(PersistentArray2[] a) {
		for(int i = 0; i < a.length; i++) {
			System.out.print(i + ":");
			if (a[i] == null) System.out.print("null");
			else
			for (int j = 0; j < 12; j++) {
				System.out.print(a[i].get(j) + " ");
			}
			System.out.println();
		}
	}
	void debug(int n) {
		int[] a = new int[n];
		for (int i = 0; i < n; i++) a[i] = get(i);
		// tr(a);
		tr(a[0], a[n/2], a[n-1]);
	}
	public static void tr(Object...o) {
		System.err.println(Arrays.deepToString(o));
	}


}
