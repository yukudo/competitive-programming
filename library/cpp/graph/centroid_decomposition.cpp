/**
* 木の重心分解（Centroid Decomposition）	
* その頂点を取り除くことによってできる最大の部分木が最小になる点を重心という。	
* 任意の木において、重心を取り除くと、残った部分木の頂点数は n/2 以下になる。	
*	
* 重心を見つけるには以下のようにする：	
* １．今訪れている頂点を v とする。	
* ２．vに隣接する部分木の頂点数が n/2 より大きいものが無ければ終了。	
* ３．vに隣接する部分木の頂点数が n/2 より大きいものがあれば、そこへ移動。１．に戻る	
*	
* 以上の処理を再帰的に繰り返せば毎回サイズが半分になっていくので
* 全体で O(nlogn)で分割を終えられる。	
*/

const int MAX_N = 212345;
vector<int> g[MAX_N];

int subtreeSize[MAX_N];
bool seen[MAX_N];
vector<int> centroid_tree[MAX_N];

int searchCentroid(int v, int N) {
  for (;;) {
    bool more = false;
    for (int u : g[v]) if (!seen[u]) {
      if (subtreeSize[u] < subtreeSize[v] && subtreeSize[u] * 2 > N) {
        v = u;
        more = true;
        break;
      }
    }
    if (!more) break;
  }
  return v;
}

int computeSubtreeSize(int v, int prev) {
  int c = 1;
  for (int u : g[v]) if (u != prev && !seen[u]) c += computeSubtreeSize(u, v);
  return subtreeSize[v] = c;
}

// 再帰的に重心分解を行って木を降りていくテンプレート
int centroidDecomposition(int v) {
  int n = computeSubtreeSize(v, -1);
  int centroid = searchCentroid(v, n);

  // centroid についてなにか処理をする。seenは必ずつける。
  seen[centroid] = true;
  // 何か
  
  // 残りの部分を再帰的に
  for (int sub : g[centroid]) if (!seen[sub]) {
    auto next_centroid = centroidDecomposition(sub);
    centroid_tree[centroid].push_back(next_centroid);
  }

  return centroid;
}
