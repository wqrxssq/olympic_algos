#pragma GCC optimize("O3,unroll-loops")

#include <math.h>

#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vll = vector<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vpii = vector<pii>;
using ld = long double;

const double EPS = 5e-6;
const double PI = acos(-1);
const int INF = 1e9;
const ll INFLL = 1e18;
const int MOD = 1e9 + 7;

#define all(_x) _x.begin(), _x.end()
#define sz(_x) _x.size()
#define rall(_x) _x.rbegin(), _x.rend()
#define pb push_back
#define ff first
#define ss second
#define display(_x)                       \
    for (auto el : _x) cout << el << ' '; \
    cout << '\n'
#define cin_arr(_x) \
    for (auto &el : _x) cin >> el;
#define fast_input ios_base::sync_with_stdio(0)
#define setpr cout << setprecision(9) << fixed

struct Point {
    ll x, y;
};

double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

struct CellHash {
    size_t operator()(const pll& p) const {
        return (size_t)(p.first * 0x9e3779b97f4a7c15ULL ^ (p.second<<1));
    }
};

const int MAXN = 2e5;
int n;
Point a[MAXN];
unordered_map<pll, vi, CellHash> grid;

mt19937 rnd(1);

void rebuild(int k, double L) {
    grid.clear();
    for (int i = 0; i <= k; i++) {
        ll cx = a[i].x / L;
        ll cy = a[i].y / L;
        grid[{cx, cy}].pb(i);
    }
}

double calc(int pos, double L) {
    ll cx = a[pos].x / L;
    ll cy = a[pos].y / L;
    vector<Point> t;
    for (ll dx = -1; dx <= 1; dx++) {
        for (ll dy = -1; dy <= 1; dy++) {
            auto it = grid.find({cx + dx, cy + dy});
            if (it == grid.end()) {
                continue;
            }
            for (int v : it->second) {
                if (dist(a[pos], a[v]) < L) {
                    t.pb(a[v]);
                }
            }
        }
    }

    double min_dist = INFLL;
    for (int i = 0; i < sz(t); i++) {
        for (int j = i + 1; j < sz(t); j++) {
            if (dist(t[i], t[j]) < L) {
                min_dist = min(min_dist, max({dist(t[i], t[j]), dist(t[i], a[pos]), dist(t[j], a[pos])}));
            }
        }
    }
    return min_dist;
}

void solve() {
    cin >> n;
    ll minx = 1e18, maxx = -1e18, miny = 1e18, maxy = -1e18;
    for(int i = 0; i < n; i++){
        cin >> a[i].x >> a[i].y;
    }

    shuffle(a, a + n, rnd);
    grid.reserve(MAXN * 4);

    double L = max({dist(a[0], a[1]), dist(a[0], a[2]), dist(a[1], a[2])});
    rebuild(2, L);

    for (int i = 3; i < n; i++) {
        double dL = calc(i, L);
        if (dL < L) {
            L = dL;
            rebuild(i, L);
        } else {
            grid[{a[i].x / L, a[i].y / L}].pb(i);
        }
    }

    cout << L << '\n';
}

int main() {
    fast_input;
#ifdef __APPLE__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    setpr;
    solve();
    return 0;
}