	// pair(a[i], i)  をソートして i のほうだけ返す
	// a[] は変更しない
	int[] indexSort(long[] a) {
		int n = a.length;
		long[][] x = new long[n][];
		for (int i = 0; i < n; i++) x[i] = new long[] { a[i], i };
		Arrays.sort(x, 0, n, new Comparator<long[]>(){
			public int compare(long[] a, long[] b){
				return Long.compare(a[0], b[0]);
			}
		});
		int[] ids = new int[n];
		for (int i = 0; i < n; i++) ids[i] = (int)x[i][1];
		return ids;
	}
