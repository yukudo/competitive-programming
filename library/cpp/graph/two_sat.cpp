/**
N個のブール変数と、()∧()∧...という式(カッコの中は、xか￢xが2つ∨で繋がってる形)という式が与えられるので、
式を真にするように変数の値をセットできるかどうか判定する。

各変数とその否定に対応する頂点からなる頂点数2Nのグラフを作り、(x∨y) == (￢x⇒y) == (￢y⇒x)なので、それに対応する有向辺をグラフに追加する。
そのグラフを強連結成分分解する。同じ強連結成分の頂点は、その定義から、x⇒yかつy⇒xであり、
その頂点に対応する変数は、同じ値にセットしなければならないことがわかる。
同じ強連結成分にxと￢xが同時に含まれていると、式を真にすることは出来ない。含まれない時はできる。

xを含む強連結成分のトポロジカル順序が￢xを含む強連結成分のトポロジカル順序よりも後ろ⇔xが真

グラフが、辺a→bのとき必ず辺b→aも成り立つなら、（普通の）連結成分に分解するだけでよい（強連結成分分解でもよい）。

「各要素にAかBを割り当てて全体でとある条件を満足させろ」みたいな問題は2-SATで解けるかもしれない。

局所的にダメな条件を列挙して∧でつなげることも多い。￢(x∧y)∧...はド・モルガンの法則で、(￢x∨￢y)∧...に書き換え可能。
**/ 

struct TwoSAT {
  const int N;
  vector<vector<int>> g, r;
  TwoSAT(int N): N(N) {
    g = vector<vector<int>>(2*N);
    r = vector<vector<int>>(2*N);
  }
  // (a == a_val || b == b_val)
  void add_cond(int a, bool a_val, int b, bool b_val) {
    int x = 2 * a + (a_val ? 1 : 0);
    int y = 2 * b + (b_val ? 1 : 0);
    g[x^1].push_back(y);
    g[y^1].push_back(x);
    r[y].push_back(x^1);
    r[x].push_back(y^1);
  }
  // !(a == a_val && b == b_val)
  void add_forbid(int a, bool a_val, int b, bool b_val) {
    add_cond(a, !a_val, b, !b_val);
  }

  vector<int> sccid;
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
    sccnum = 0;
    sccid = vector<int>(2 * N);
    vector<int> order;
    REP(i, 2*N) dfs(i, order);
    fill(ALL(sccid), -1);
    sccnum = 0;
    for (int i = (int)order.size() - 1; i >= 0; i--) if (sccid[order[i]] == -1) {
      rdfs(order[i], sccnum);
      sccnum++;
    }
  }
  // 割り当てを一つ返す。存在しない場合は長さ0を返す。
  vector<int> solve() {
    vector<int> res(N);
    REP(i, N) {
      if (sccid[2*i] != -1 && sccid[2*i] == sccid[2*i+1]) return {};
      res[i] = sccid[2*i+1] > sccid[2*i] ? 1 : 0;
    }
    return res;
  }
};
