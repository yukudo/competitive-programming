package ds.persistent;

import java.util.Arrays;


/**
 * 永続配列
 * 永続とは、状態を変更すると新しいオブジェクトが返される。前の状態は生き続ける、という性質。
 * 
 * 二分探索木の永続化による実装。
 * ちゃんと平衡させるのは面倒なので、始めにメモリを確保してしまい木の形は固定とする。
 *
 * 使いどころとしては、他と大部分が同じ (配列|SegTree|BST) が大量に必要な場合。
 *
 * まだ構造が入ってないからあまり使えない。
 * 中間ノードに範囲の和や最大値を持たせてあげよう。
 *
 * - get(i)
 * - set(i, val)
 *
 */
public class PersistentArray {

	static class Node {
		Node[] ch = new Node[2];
		int val; // val は leaf にだけ持たせる
		public Node() { }
		public Node(int val) { this.val = val; }

		/**
		 * O(logn)
		 */
		int get(int nl, int nr, int index) {
			Node node = this;
			if (nl + 1 == nr) return node.val;

			int middle = (nl + nr) >> 1;
			Node next = (index < middle) ? node.ch[0] : node.ch[1];
			if (next == null) return 0; // default value

			if (index < middle)
				return next.get(nl, middle, index);
			else
				return next.get(middle, nr, index);
		}

		/**
		 * O(logn)
		 * 呼び出すごとにO(logn)のメモリが新たに確保される。
		 */
		Node set(int nl, int nr, int index, int val) {
			Node alter = new Node();

			if (nl + 1 == nr) {
				alter.val = val;
				return alter;
			}

			int middle = (nl + nr) >> 1;
			Node next = (index < middle) ? ch[0] : ch[1];
			if (next == null) next = new Node();

			if (index < middle) {
				alter.ch[0] = next.set(nl, middle, index, val);
				alter.ch[1] = this.ch[1];
			} else {
				alter.ch[0] = this.ch[0];
				alter.ch[1] = next.set(middle, nr, index, val);
			}
			return alter;
		}
	}

	int n;
	Node root;

	/**
	 * コンストラクタ
	 * 大きさ n の配列を確保した風にする。
	 * @param n
	 */
	public PersistentArray(int n) {
		this.n = n;
		root = new Node();
	}

	/**
	 * @param node
	 */
	private PersistentArray(int n, Node node) {
		this.n = n;
		this.root = node;
	}

	public int get(int index) {
		return root.get(0, n, index);
	}

	public PersistentArray set(int index, int val) {
		return new PersistentArray(n, root.set(0, n, index, val));
	}


	void debug() {
		int[] a = new int[n];
		for (int i = 0; i < n; i++) a[i] = get(i);
		// tr(a);
		tr(a[0], a[n/2], a[n-1]);
	}


	public static void tr(Object...o) {
		System.err.println(Arrays.deepToString(o));
	}


	/**
	 * 動作確認用メイン
	 */
	public static void main(String[] args) {
		long start = System.currentTimeMillis();
		int MOD = 10007;
		int n = 200000;
		PersistentArray a = new PersistentArray(n);
		int q = 200000;

		PersistentArray mid = null;
		for (int i = 0; i < q; i++) {
			a = a.set(i, i);
			if (i == q / 2) mid = a;
		}

		a.debug();
		mid.debug();

		long end = System.currentTimeMillis();
		tr(end - start + "ms");
	}

}
