#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <deque>
#include <queue>
#include <string>
#include <stack>
#include <cassert>
#include <iomanip>
#include <random>
#include <chrono>
#include <cstring>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using vi = vector <int>;
using vvi = vector <vi>;
using vll = vector <ll>;
using pii = pair <int, int>;
using vpii = vector <pii>;

#define all(_x) _x.begin(), _x.end()
#define rall(_x) _x.rbegin(), _x.rend()
#define sz(_x) (int)_x.size()
#define ff first
#define ss second
#define pb push_back
#define display(_x) for (int x : a) cout << x << ' '; cout << '\n';
#define fast_input ios_base::sync_with_stdio(0); cin.tie(0);
#define cin_arr(_x) for (int &x : a) cin >> x;

const int INF = 1e9;
const int MOD = 1e9 + 7;
const double EPS = 1e-6;

struct rectangle {
    // x1 <= x2
    // y1 <= y2
    int x1, x2;
    int y1, y2;
};

rectangle intersect(rectangle a, rectangle b) {
    rectangle res = {max(a.x1, b.x1), min(a.x2, b.x2), max(a.y1, b.y1), min(a.y2, b.y2)};
    if (res.x1 > res.x2 || res.y1 > res.y2) {
        res = {0, 0, 0, 0};
    }
    return res;
}

const int MAXN = 128;
const int MAXH = 7;
int n, m;
rectangle a[MAXN][MAXN];
rectangle sparse_table[MAXH][MAXH][MAXN][MAXN];

int log(int n) {
    return 31 - __builtin_clz(n);
}

rectangle rmq(int x1, int y1, int x2, int y2) {
    // найти наибольшую степень двойки в которую "влазит" их разность
    int t1 = log(x2 - x1);
    int t2 = log(y2 - y1);
    // минимум находится из 4 квадратов
    return intersect(intersect(sparse_table[t1][t2][x1][y1], sparse_table[t1][t2][x1][y2 - (1 << t2)]),
           intersect(sparse_table[t1][t2][x2 - (1 << t1)][y1], sparse_table[t1][t2][x2 - (1 << t1)][y2 - (1 << t2)]));
}

void build() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            sparse_table[0][0][i][j] = a[i][j];
    for (int k = 0; (1 << (k + 1)) <= n; k++)
        for (int j = 0; j < m; j++)
            for (int i = 0; i + (1 << k) < n; i++)
                sparse_table[k + 1][0][i][j] = intersect(sparse_table[k][0][i][j], sparse_table[k][0][i + (1 << k)][j]);
    for (int k = 0; (1 << (k + 1)) <= m; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j + (1 << k) < m; j++)
                sparse_table[0][k + 1][i][j] = intersect(sparse_table[0][k][i][j], sparse_table[0][k][i][j + (1 << k)]);
     
    for (int i = 0; (1 << (i + 1)) <= n; i++)
        for (int j = 0; (1 << (j + 1)) <= m; j++)
            for (int z = 0; z + (1 << i) < n; z++)
                for (int k = 0; k + (1 << j) < m; k++)
                    sparse_table[i + 1][j + 1][z][k] = intersect(intersect(sparse_table[i][j][z][k],
                                                           sparse_table[i][j][z][k + (1 << j)]),
                                                           intersect(sparse_table[i][j][z + (1 << i)][k],
                                                               sparse_table[i][j][z + (1 << i)][k + (1 << j)]));
}

int gen(int A, int B, int v0) {
    return (1LL * A * v0 + B) % MOD;
}

int get_s(rectangle a) {
    return (1LL * (a.x2 - a.x1) * (a.y2 - a.y1)) % MOD;
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            if (x1 > x2)
                swap(x1, x2);
            if (y1 > y2)
                swap(y1, y2);
            a[i][j] = {x1, x2, y1, y2};
        }
    }

    build();

    int q;
    cin >> q;
    int A, B, v0;
    cin >> A >> B >> v0;
    int res = 0;
    for (int i = 0; i < q; i++) {
        v0 = gen(A, B, v0);
        int r1 = v0 % n;
        v0 = gen(A, B, v0);
        int c1 = v0 % m;
        v0 = gen(A, B, v0);
        int r2 = v0 % n;
        v0 = gen(A, B, v0);
        int c2 = v0 % m;

        int r_low = min(r1, r2), r_high = max(r1, r2) + 1;
        int c_low = min(c1, c2), c_high = max(c1, c2) + 1;

        res = (res + get_s(rmq(r_low, c_low, r_high, c_high))) % MOD;
    }
    cout << res << '\n';
}

int main() {
    fast_input;
#ifdef __APPLE__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    solve();
}