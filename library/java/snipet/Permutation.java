
/**
An = {0..n-1} の permutation を考える。
indexToPerm(int j, int n); ... 長さ n の配列の j 番目の順列
permToIndex(p[]); ... 順列 p は何番目か

番目は0から数える。
0 : {0, 1, 2} 
1 : {0, 2, 1} 
2 : {1, 0, 2} 
3 : {1, 2, 0} 
4 : {2, 0, 1} 
5 : {2, 1, 0} 
*/
public class Permutation {
	static long[] fact;
	static {
		fact = new long[21];
		fact[0] = 1;
		for (int i = 1; i < fact.length; i++) fact[i] = fact[i-1] * i;
	}
	/** 長さ n の配列の j 番目の順列 */
	static int[] indexToPerm(long j, int n) {
		int[] p = new int[n];
		indexToPerm(j, n, p, 0);
		return p;
	}
	static void indexToPerm(long j, int n, int[] out, int s) {
		if (n == 1) { return; }
		out[s] = (int)(j / fact[n-1]);
		indexToPerm((j % fact[n-1]), n - 1, out, s + 1);
		for (int i = s + 1; i < s + n; i++) {
			if (out[i] >= out[s]) out[i]++;
		}
	}

	/**
	 * p は破壊される
	 */
	static long permToIndex(int[] p) {
		long res = 0;
		for (int i = 0; i + 1 < p.length; i++) {
			if (p.length - i == 2) {
				res += p[i];
			} else {
				res += fact[p.length - i - 1] * p[i];
				for (int j = i + 1; j < p.length; j++) if (p[j] > p[i]) p[j]--;
			}
		}
		return res;
	}

}