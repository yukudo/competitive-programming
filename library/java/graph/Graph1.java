package graph;

import java.util.ArrayList;

public class Graph1 {

	static class V extends ArrayList<V> {
		int val;
	}

	public static void main(String[] args) {

		V[] vs = new V[1000];
		for (int i = 0; i < vs.length; i++) {
			vs[i] = new V();
			vs[i].val = i;
		}
		vs[3].add(vs[4]);
	}
}
