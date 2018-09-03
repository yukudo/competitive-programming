package ds.segtree;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;


// 未整理
// https://www.hackerrank.com/challenges/quadrant-queries
// 遅延評価つきの SegmentTree の例。
// 範囲更新と範囲取得が可能。
// この問題では[l, r)の点が第i象限にいくつあるかをint[4]で持つ。
// 範囲全体を覆うような更新クエリは、子に対して更新処理を予約するのみにとどめ、
// 実際に更新処理を行うのをgetのときまで遅延させる。
public class LazySegtree {
	public static void main(String[] args) {
		try {
			new LazySegtree().run();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	void solve() {
		int n = sc.nextInt();
		int[] a = new int[n];
		for (int i = 0; i < n; i++) {
			int x = sc.nextInt();
			int y = sc.nextInt();
			a[i] = (x > 0 && y > 0) ? 0 :
				(x < 0 && y > 0) ? 1 :
				(x < 0 && y < 0) ? 2 : 3;
		}
		SegmentTree tree = new SegmentTree(a);
		int q = sc.nextInt();
		for (;q-->0;) {
			String c = sc.next();
			int i = sc.nextInt();
			int j = sc.nextInt();
			if (c.equals("X")) {
				tree.update(i-1, j, 1);
			} else if (c.equals("Y")) {
				tree.update(i-1, j, 2);
			} else if (c.equals("C")) {
				int[] res = tree.get(i-1, j);
				out.println(res[0] + " " + res[1] + " " + res[2] + " " + res[3]);
			}
		}
	}
	
	static class SegmentTree {
		static final int[] ZERO = {0, 0, 0, 0};
		int n;
		int size;
		int[][] val;
		int[] request;

		SegmentTree(int[] a) {
			this.n = a.length;
			this.size = n <= 1 ? 1 : (Integer.highestOneBit(n - 1) << 2);
			val = new int[size][4];
			request = new int[size];
			for (int i = 0; i < a.length; i++) {
				add(i, a[i], 0, 0, n);
			}
			return;
		}
		
		void add(int p, int x, int k, int l, int r) {
			// ノード番号 k が、範囲 [l,r)。
			if (r - l == 1) {
				val[k][x]++;
				return;
			}
			if (p < (l + r) / 2) 
				add(p, x, k * 2 + 1, l, (l + r) / 2);
			else
				add(p, x, k * 2 + 2, (l + r) / 2, r);
			for (int i = 0; i < 4; i++) val[k][i] = val[k*2+1][i] + val[k*2+2][i];
		}

		/**
		 * 区間[a, b)を更新する。 x == 1 == refrect X ,  x == 2 == refrect Y
		 */
		void update(int a, int b, int x) {
			update(a, b, x, 0, 0, n);
		}
		private void update(int a, int b, int x, int k, int l, int r)
		{
			// ノード番号 k が、範囲 [l,r)。
			
			if (r <= a || b <= l) {
				levy(k);
			} 
			else if (a <= l && r <= b){
				request[k] ^= x;
				levy(k);
			}
			else {
				if (k * 2 + 1 < size) request[k * 2 + 1] ^= request[k];
				if (k * 2 + 2 < size) request[k * 2 + 2] ^= request[k];
				update(a, b, x, k * 2 + 1, l, (l + r) / 2);
				update(a, b, x, k * 2 + 2, (l + r) / 2, r);
				for (int i = 0; i < 4; i++) val[k][i] = val[k*2+1][i] + val[k*2+2][i];
				request[k] = 0;
			}
		}
		private void levy(int k) {
			if (k * 2 + 1 < size) request[k * 2 + 1] ^= request[k];
			if (k * 2 + 2 < size) request[k * 2 + 2] ^= request[k];
			if ((request[k] & 1) != 0) { // x軸対称
				swap(val[k], 0, 3);
				swap(val[k], 1, 2);
				request[k] ^= 1;
			} 
			if ((request[k] & 2) != 0) { // y軸対称
				swap(val[k], 0, 1);
				swap(val[k], 2, 3);
				request[k] ^= 2;
			}
		}

		/**
		 * 区間[a, b)
		 */
		int[] get(int a, int b) {
			return get(a, b, 0, 0, n);
		}

		private int[] get(int a, int b, int k, int l, int r)
		{
			// ノード番号 k が、範囲 [l,r)。
			levy(k);
			
			if (b <= l || r <= a){ //[a, b)と[l, r)が全く交差しない場合
				return ZERO;
			}
			else if (a <= l && r <= b){ //完全に内包されていれば
				return val[k];
			}
			else { //[l, r)と[a, b)が交差していれば
				int[] res = new int[4];
				arrayAdd(res, get(a, b, k * 2 + 1, l, (l + r) / 2));
				arrayAdd(res, get(a, b, k * 2 + 2, (l + r) / 2, r));
				return res;
			}
		}
		
		static void swap(int[] a, int i, int j) {
			int t = a[i]; a[i] = a[j]; a[j] = t;
		}
		static int[] arrayAdd(int[] a, int[] b) {
			for (int i = 0; i < a.length; i++) a[i] += b[i];
			return a;
		}
	}
	
	
	MyScanner sc = null;
	PrintWriter out = null;
	public void run() throws Exception {
		sc = new MyScanner(System.in);
		out = new PrintWriter(System.out);
		for (;sc.hasNext();) {
			solve();
			out.flush();
		}
		out.close();
	}

	class MyScanner {
		String line;
		BufferedReader reader;
		StringTokenizer tokenizer;

		public MyScanner(InputStream stream) {
			reader = new BufferedReader(new InputStreamReader(stream));
			tokenizer = null;
		}
		public void eat() {
			while (tokenizer == null || !tokenizer.hasMoreTokens()) {
				try {
					line = reader.readLine();
					if (line == null) {
						tokenizer = null;
						return;
					}
					tokenizer = new StringTokenizer(line);
				} catch (IOException e) {
					throw new RuntimeException(e);
				}
			}
		}
		public String next() {
			eat();
			return tokenizer.nextToken();
		}
		public String nextLine() {
			try {
				return reader.readLine();
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}
		public boolean hasNext() {
			eat();
			return (tokenizer != null && tokenizer.hasMoreElements());
		}
		public int nextInt() {
			return Integer.parseInt(next());
		}
		public long nextLong() {
			return Long.parseLong(next());
		}
		public double nextDouble() {
			return Double.parseDouble(next());
		}
		public int[] nextIntArray(int n) {
			int[] a = new int[n];
			for (int i = 0; i < n; i++) a[i] = nextInt();
			return a;
		}
	}
}
