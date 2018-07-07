public class UpperBound {

// lower_bound / upper_bound

// 比較が < と <= の違いのみ。
// (k の出現回数) == upper_bound(a, k) - lower_bound(a, k)

	int lower_bound(int[] a, int val) {
		int lo = -1;
		int hi = a.length;
		while (hi - lo > 1) {
			int mid = (hi + lo) >> 1;
			if (a[mid] < val) lo = mid; else hi = mid;
		}
		return hi;
	}

	int upper_bound(int[] a, int val) {
		int lo = -1;
		int hi = a.length;
		while (hi - lo > 1) {
			int mid = (hi + lo) >> 1;
			if (a[mid] <= val) lo = mid; else hi = mid;
		}
		return hi;
	}

	// 範囲つきのバージョン
	
	int lower_bound(int[] a, int begin, int end, int val) {
		int lo = begin - 1;
		int hi = end;
		while (hi - lo > 1) {
			int mid = (hi + lo) >> 1;
			if (a[mid] < val) lo = mid; else hi = mid;
		}
		return hi;
	}

	int upper_bound(int[] a, int begin, int end, int val) {
		int lo = begin - 1;
		int hi = end;
		while (hi - lo > 1) {
			int mid = (hi + lo) >> 1;
			if (a[mid] <= val) lo = mid; else hi = mid;
		}
		return hi;
	}

}
