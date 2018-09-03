package ds.persistent;

import java.util.ArrayList;
import java.util.Arrays;

/**
 * 永続Stack
 * linked list の永続化による実装。
 * 永続とは、状態を変更すると新しいオブジェクトが返される。前の状態は生き続ける、という性質
 *
 * - get(i)
 *     O(logn)
 *     ダブリングして 2**x 先のポインタを保持するため、ランダムアクセスが O(logn) でできる。
 *
 * - push(val)
 *     O(logn)
 *     ダブリングポインタを張るので O(logn)かかる。
 *
 * - pop()
 *     O(1)
 *
 *  http://www.slideshare.net/qnighy/re-15443018
 *  Crayfish Scrivener (IOI 2012, day 1)
 *
 */
public class PersistentStack {

	int size;
	PersistentStack[] ns = new PersistentStack[21];
	int val;

	private PersistentStack(int size, int val) {
		this.size = size;
		this.val = val;
	}

	public static PersistentStack getInstance() {
		return new PersistentStack(0, 0xDEADBEEF);
	}

	int size() {
		return this.size;
	}

	/**
	 * このスタックの末尾に値 val を追加する。O(logn)
	 * 更新後のスタックを返す。
	 * @param val
	 * @return
	 */
	public PersistentStack push(int val) {
		PersistentStack node = new PersistentStack(size + 1, val);
		node.ns[0] = this;
		for (int i = 0; node.ns[i] != null; i++) node.ns[i+1] = node.ns[i].ns[i];
		return node;
	}

	/**
	 * リストの先頭から runLength 番目のノードを返す
	 * @param runLength リストをたどる長さ
	 * @return
	 */
	private PersistentStack seek(int runLength) {
		PersistentStack node = this;
		int two = 0;
		while (runLength > 0) {
			if ((runLength & 1) == 1) node = node.ns[two];
			runLength >>= 1;
			two++;
		}
		return node;
	}

	/**
	 * index番目の値を返す。 O(logn)
	 * @param index
	 * @return
	 */
	public int get(int index) {
		int runLength = size - 1 - index;
		return seek(runLength).val;
	}

	/**
	 * 末尾 k 個を削除する。O(log k)
	 * 更新後のスタックを返す。
	 */
	public PersistentStack pop_back(int k) {
		return seek(k);
	}

	/**
	 * 末尾 1 個を削除する。O(1)
	 * 更新後のスタックを返す。
	 */
	public PersistentStack pop() {
		return pop_back(1);
	}

	void debug() {
		int[] a = new int[size];
		for (int i = 0; i < a.length; i++) a[i] = get(i);
		tr(a);
	}

	public static void tr(Object...o) {
		System.err.println(Arrays.deepToString(o));
	}




	/**
	 * 動作確認用メイン
	 */
	public static void main(String[] args) {
		test1();
	}

	static void test1() {
		PersistentStack s = PersistentStack.getInstance();

		ArrayList<PersistentStack> history = new ArrayList<PersistentStack>();

		s.debug(); history.add(s);

		s = s.push('A');
		s.debug(); history.add(s);

		s = s.push('B');
		s.debug(); history.add(s);

		s = history.get(history.size() - 2); // undo(1)
		s.debug(); history.add(s);

		s = s.push('C');
		s.debug(); history.add(s);

		// undo の undo
		s = history.get(history.size() - 3); // undo(2)
		s.debug(); history.add(s);

		s = s.push('D');
		s.debug(); history.add(s);

		tr(s.get(0));
	}


}
