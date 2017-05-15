package graph;

import java.util.ArrayList;

public class Graph2 {

	// エッジにも属性をつけたいバージョン

	class V {
		ArrayList<E> es = new ArrayList<E>();
		int val;
		void add(V to, int w) {
			this.es.add(new E(to, w));
		}
	}
	class E {
		V to;
		int w;
		E(V to, int w) {
			this.to = to;
			this.w = w;
		}
	}

}
