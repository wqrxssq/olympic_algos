// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>
#include <cassert>
 
using namespace std;

// #define int long long
// #define int128 __int128
// #define ld long double
// #define float128 __float128
// #define all(x) x.begin(), x.end()
// #define pb push_back
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
const int MAXN = 1000, K = 30, PW = 179, PW1 = 37, MOD = 1e9 + 1000 - 7, MOD1 = 1e9 + 7, INF = 2e9;
int n;

int h[MAXN + 1];
int parent[MAXN + 1];
double EPS = 1e-9;


vector<int> findBestMethods(int size, double target) {
    vector<double> methods;
    if (size == 10) {
        methods = {2.185565, 2.465885, 3.071615, 2.667708, 1.688393,
                   2.590848, 2.529762, 2.543601, 2.749182, 2.732403};
    } else if (size == 25) {
        methods = {3.181135, 3.878221, 4.340439, 4.025777, 2.173523,
                   4.065529, 4.107294, 3.512855, 4.529359, 4.408145};
    } else if (size == 50) {
        methods = {3.804066, 5.383856, 5.638703, 5.308961, 2.637430,
                   5.461265, 5.388613, 4.188877, 6.267547, 5.550005};
    } else if (size == 100) {
        methods = {4.393432, 6.863311, 6.220531, 6.866039, 3.032581,
                   7.291268, 7.409089, 5.225061, 8.497712, 6.776584};
    } else if (size == 200) {
        methods = {5.348751, 8.771503, 7.214957, 8.621204, 3.350827,
                   9.492062, 9.446008, 6.210173, 12.069021, 8.504677};
    } else if (size == 300) {
        methods = {5.537817, 9.980562, 7.755818, 9.742348, 3.518681,
                   11.021041, 11.156436, 6.762846, 14.558511, 11.247794};
    } else if (size == 400) {
        methods = {5.855149, 10.730117, 8.017621, 10.634304, 3.634407,
                   12.749966, 12.162976, 7.173903, 16.626668, 13.702798};
    } else if (size == 500) {
        methods = {6.080226, 11.563673, 8.181517, 11.204999, 3.897417,
                   13.737247, 13.179863, 7.716309, 18.600009, 15.719975};
    } else if (size == 750) {
        methods = {6.629989, 12.751271, 8.612399, 12.195549, 4.111325,
                   15.547751, 15.970845, 8.502986, 23.453495, 20.249136};
    } else if (size == 1000) {
        methods = {6.846231, 13.578109, 9.060868, 13.156907, 4.222215,
                   17.620883, 17.377692, 9.279635, 26.439482, 23.697571};
    } else {
        return {};
    }

    // Определяем минимальную абсолютную разницу между target и значениями
    double minDiff = 1e9;
    int best = 0;
    for (int i = 0; i < methods.size(); i++) {
        double diff = fabs(methods[i] - target);
        if (diff < minDiff) {
            minDiff = min(minDiff, diff);
            best = i;
        }
    }

    vector <int> ans;
    for (int i = 0; i < methods.size(); i++) {
        double diff = fabs(methods[i] - target);
        if (fabs(diff - minDiff) <= EPS) {
            ans.push_back(i + 1);
        }
    }

    return ans;
}

int findBestMethodsDiametr(int size, double target) {
    vector<double> methods;
    if (size == 10) {
        methods = {6.359375, 6.687500, 8.093750, 6.937500, 5.078125,
                   7.203125, 7.437500, 6.906250, 7.312500, 7.234375};
    } else if (size == 25) {
        methods = {9.875000, 11.515625, 12.640625, 11.968750, 6.968750,
                   12.218750, 12.312500, 10.875000, 13.046875, 12.859375};
    } else if (size == 50) {
        methods = {12.437500, 16.171875, 16.765625, 16.359375, 8.562500,
                   17.468750, 17.640625, 14.093750, 19.359375, 18.015625};
    } else if (size == 100) {
        methods = {15.671875, 21.796875, 21.250000, 21.718750, 10.203125,
                   25.062500, 24.765625, 16.734375, 29.328125, 24.796875};
    } else if (size == 200) {
        methods = {18.484375, 25.984375, 24.656250, 27.500000, 11.796875,
                   33.921875, 34.796875, 21.515625, 42.906250, 32.906250};
    } else if (size == 300) {
        methods = {20.515625, 30.156250, 26.843750, 32.359375, 12.609375,
                   40.984375, 40.265625, 23.218750, 51.078125, 44.781250};
    } else if (size == 400) {
        methods = {21.718750, 33.328125, 28.796875, 34.375000, 13.312500,
                   46.953125, 47.625000, 25.281250, 62.828125, 53.468750};
    } else if (size == 500) {
        methods = {22.562500, 35.343750, 29.125000, 37.281250, 13.828125,
                   51.906250, 51.062500, 28.125000, 70.562500, 62.531250};
    } else if (size == 750) {
        methods = {24.609375, 39.125000, 31.671875, 41.125000, 14.671875,
                   61.656250, 61.156250, 30.375000, 89.875000, 82.406250};
    } else if (size == 1000) {
        methods = {26.437500, 41.687500, 32.937500, 43.812500, 15.406250,
                   68.312500, 69.828125, 33.406250, 101.562500, 96.250000};
    } else {
        cout << "Unknown size" << endl;
        return 1;
    }
    
    double minDiff = 1e9;
    int best = 0;
    for (int i = 0; i < methods.size(); i++) {
        double diff = fabs(methods[i] - target);
        if (diff < minDiff) {
            minDiff = min(minDiff, diff);
            best = i;
        }
    }

    return best + 1;
}

void dfs(int v, int p, vector<vector<int>> &g) {
    h[v] = (p != -1 ? h[p] + 1 : 0);
    parent[v] = p;
    for (int u : g[v]) {
        if (u != p) {
            dfs(u, v, g);
        }
    }
}

vector<int> get_diam(vector<vector<int>> &g) {
    h[1] = 0;
    dfs(1, 1, g);
    int best = 1;
    for (int i = 1; i <= n; ++i) {
        if (h[best] < h[i])
            best = i;
    }
    h[best] = 0;
    int start = best;
    dfs(best, best, g);
    vector<int> path;
    for (int i = 1; i <= n; ++i) {
        if (h[best] < h[i])
            best = i;
    }
    while (best != start) {
        path.push_back(best);
        best = parent[best];
    }
    path.push_back(start);
    return path;
}


double get_average_height(int root, int n, vector<vector<int>>& g) {
    double res = 0;
    int cnt = 0;
    for (int v = 1; v <= n; v++) {
        cnt += (g[v].size() == 1 && v != root);
        res += (g[v].size() == 1 && v != root ? h[v] : 0);
    }
    return res / cnt;
}

void DFS_GOIDA(int u, int p, vector<vector<int>> &g, vector<int> &c) {
    for (auto it: g[u]) {
        if (p == it)
            continue;
        c[it] = (c[u] ^ 1);
        DFS_GOIDA(it, u, g, c);
    }
}

int pred_6_7(vector<vector<int>> &g) {
    vector<int> coloring(n + 1, 0);
    DFS_GOIDA(1, -1, g, coloring);
    int c0 = 0, c1 = 0;
    for (int i = 1; i <= n; ++i) {
        if (coloring[i])
            c1++;
        else
            c0++;
    }
    if (abs(c0 - c1) <= 1) {
        return {7};
    } else {
        return {6};
    }
}

void solve() {
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> path = get_diam(g);
    int root = path[path.size() / 2];
    dfs(root, -1, g);
    double average_height = get_average_height(root, n, g);
    
    int b = findBestMethodsDiametr(n, path.size());
    if (b == 6 || b == 7) {
        b = pred_6_7(g);
    }

    if (b == 3 || b == 8) {
        if (rng() % 2 == 0) {
            b = 3;
        } else {
            b = 8;
        }
    }

    cout << "1\n";
    cout << b << '\n';
}

signed main() {
#ifdef __APPLE__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << setprecision(6) << fixed;
    int T = 1;
    cin >> T; cin >> n;   
    while (T--) {
        solve();
    }
}