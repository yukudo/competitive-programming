// ## 強連結成分分解
// 何番の頂点は何番の連結成分に含まれるっていう配列を生成．
// Step 1. 番号がついていないノードをランダムに選び，そのノードを始点としてdfsし、閉じた順にノードに番号をつけていく．
// Step 2. 枝の向きを変えた，逆グラフをつくる．
// Step 3. まだ強連結成分に属していないノードの中で，番号の一番大きなノードから(まだ強連結成分に属していないノードのみを経由して)到達できるノードの集合が1つの強連結成分。
// O(V + E)
// 頂点が少ないときにはワーシャルフロイドで楽できる。

int sccid[MAX_N];
int sccnum;
void dfs(int p, vector<int>& order) {
  if (sccid[p] != 0) return;
  sccid[p] = 1;
  for (int i : g[p]) dfs(i, order);
  order.push_back(p);
}
void rdfs(int p, int id) {
  if (sccid[p] != -1) return;
  sccid[p] = id;
  for (int i : r[p]) rdfs(i, id);
}
void scc() {
  vector<int> order;
  CLR(sccid, 0);
  REP(i, N) dfs(i, order);
  CLR(sccid, -1);
  sccnum = 0;
  for (int i = (int)order.size() - 1; i >= 0; i--) if (sccid[order[i]] == -1) {
    rdfs(order[i], sccnum);
    sccnum++;
  }
}
