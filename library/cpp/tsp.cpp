// C:\project\zzz\Typical-MM\TravelingSalesman\tester>
// java Tester -vis -seed 2 -exec "wsl /mnt/c/project/zzz/Typical-MM/TravelingSalesman/solution/a.out" -num

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1005;
double dist[MAX_N][MAX_N];

vector<int> tsp(const vector<int> posX, const vector<int> posY) {
    const int N = (int)posX.size();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            const double dx = posX[i] - posX[j];
            const double dy = posY[i] - posY[j];
            dist[i][j] = sqrt(dx * dx + dy * dy);
        }
    }

    vector<int> ans;
    for (int i = 0; i < N; i++) ans.push_back(i);

    auto D = [&](const int i, const int j) {
        return dist[ans[i % N]][ans[j % N]];
    };

    for (;;) {
        bool update = false;

        // 2-opt
        for (int i = 0; i < N; i++) {
            for (int j = i + 2; j <= N; j++) {
                double before = D(i-1, i) + D(j-1, j);
                double after = D(i-1, j-1) + D(i, j);
                if (before > after) {
                    reverse(ans.begin() + i, ans.begin() + j);
                    update = true;
                }
            }
        }

        // 3-opt
        for (int i1 = 0; i1 < N; i1++)      { const int i2 = i1 + 1;
        for (int i3 = i2 + 1; i3 < N; i3++) { const int i4 = i3 + 1;
        for (int i5 = i4 + 1; i5 < N; i5++) { const int i6 = i5 + 1;
            int d[5], min = 0;
            d[0] = D(i1, i2) + D(i3, i4) + D(i5, i6);
            d[1] = D(i1, i3) + D(i2, i5) + D(i4, i6);
            d[2] = D(i1, i4) + D(i5, i2) + D(i3, i6);
            d[3] = D(i1, i4) + D(i5, i3) + D(i2, i6);
            d[4] = D(i1, i5) + D(i4, i2) + D(i3, i6);
            for (int m = 1; m <= 4; m++) if (d[m] < d[min]) min = m;
            if (min == 0) continue;
            update = true;
            if (min == 1) {
                reverse(ans.begin() + i2, ans.begin() + i4);
                reverse(ans.begin() + i4, ans.begin() + i6);
            }
            if (min == 2) {
                reverse(ans.begin() + i2, ans.begin() + i4);
                reverse(ans.begin() + i4, ans.begin() + i6);
                reverse(ans.begin() + i2, ans.begin() + i6);
            }
            if (min == 3) {
                reverse(ans.begin() + i2, ans.begin() + i6);
                reverse(ans.begin() + i2, ans.begin() + i4);
            }
            if (min == 4) {
                reverse(ans.begin() + i2, ans.begin() + i4);
                reverse(ans.begin() + i2, ans.begin() + i6);
            }
        }
        }
        }

        if (!update) break;
    }

    return ans;
}

void experience() {
    int N = 3 * 2;

    map< vector<int>, vector< pair<int,int> > > process; // reverse によって順列をそれにする対象手順。
    {
        vector<int> v;
        for (int i = 0; i < N; i++) v.push_back(i + 1);
        
        priority_queue< pair<int, vector<int> > > q;
        q.push( {0, v} );
        process[v] = vector< pair<int,int> >();
        
        while (!q.empty()) {
            int cost = -q.top().first;
            v = q.top().second; q.pop();
            vector<pair<int,int>> ps = process[v];
            for (int i = 1; i < N; i += 2) {
                for (int j = i; j <= N; j += 2) {
                    reverse(v.begin() + i, v.begin() + j);
                    if (process.count(v) == 0) {
                        int cost2 = cost + j - i;
                        auto ps2 = ps;
                        ps2.push_back({i, j});
                        process[v] = ps2;
                        q.push({-cost2, v});
                    }
                    reverse(v.begin() + i, v.begin() + j);
                }
            }
        }
    }

    {
        vector<int> v;
        for (int i = 0; i < N; i++) v.push_back(i + 1);
        do {
            vector<int> idx(N+1);
            for (int i = 0; i < v.size(); i++) idx[ v[i] ] = i+1;

            bool ok = idx[1] == 1 && idx[N] == N && abs(idx[2] - idx[3]) <= 1 && abs(idx[4] - idx[5]) <= 1;
            if (ok) {
                for (int i = 0; i < v.size(); i++) {
                    cout << v[i] << " ";
                }
                cout << ":";
                for (auto p : process[v]) {
                    cout << "(" << p.first + 1  << "," << p.second + 1 << ")";
                }
                cout << endl;
            }
        } while (next_permutation(v.begin(), v.end()));

    }

    return;
}

int main () {

    // experience(); return 0;

    int N; cin >> N;
    vector<int> posX(N), posY(N);
    for (int i = 0; i < N; i++) cin >> posX[i] >> posY[i];

    vector<int> ans = tsp(posX, posY);
    for (int i = 0; i < N; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}

