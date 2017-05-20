package flow;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

public class Dinic {

	static final int INF = 1001001001;
	
	
	int dinic(V s, V t) {
		int flow = 0;
		for (int p = 1;; p++) {
			Queue<V> que = new LinkedList<V>();
			s.level = 0;
			s.p = p;
			que.offer(s);
			while (!que.isEmpty()) {
				V v = que.poll();
				v.iter = v.es.size() - 1;
				for (E e : v.es)
					if (e.to.p < p && e.cap > 0) {
						e.to.level = v.level + 1;
						e.to.p = p;
						que.offer(e.to);
					}
			}
			if (t.p < p) return flow;
			for (int f; (f = dfs(s, t, INF)) > 0;) flow += f;
		}
	}

	int dfs(V v, V t, int f) {
		if (v == t) return f;
		for (; v.iter >= 0; v.iter--) {
			E e = v.es.get(v.iter);
			if (v.level < e.to.level && e.cap > 0) {
				int d = dfs(e.to, t, Math.min(f, e.cap));
				if (d > 0) {
					e.cap -= d;
					e.rev.cap += d;
					return d;
				}
			}
		}
		return 0;
	}

	class V {
		ArrayList<E> es = new ArrayList<E>();
		int level, p, iter;
		
		void add(V to, int cap) {
			E e = new E(to, cap);
			E rev = new E(this, 0);
			e.rev = rev;
			rev.rev = e;
			es.add(e);
			to.es.add(rev);
		}
	}

	class E {
		V to;
		E rev;
		int cap;

		E(V to, int cap) {
			this.to = to;
			this.cap = cap;
		}
	}

}
