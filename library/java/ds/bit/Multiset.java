package ds.bit;

/**
 * 入れる値の上限が 10 万程度のとき、multiset<int> の高速な実装が可能。
 * 座標圧縮してから使うことも多い。 
 */
public class Multiset {
	BIT bit;
	public Multiset(int n) {
		bit = new BIT(n);
	}

	void insert(int x) {
		bit.add(x, 1);
	}

	void erase(int x) {
		bit.add(x, -1);
	}

	int count(int x) {
		return (int)bit.range(x,x);
	}

	int countLowerThan(int x) {
		return (int)bit.range(x-1);
	}

	/** 0-indexed で、i番目に小さい要素を取得 */
	int get(int i) {
		return bit.find(i+1);
	}
}
