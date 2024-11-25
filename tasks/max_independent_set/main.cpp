#pragma GCC optimize("O3,unroll-loops")

#include <math.h>

#include <algorithm>
#include <bitset>
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
#include <climits>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vll = vector<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vpii = vector<pii>;
const double PI = acos(-1);
const double EPS = 1e-6;
const int INF = 1e9;
const ll INFLL = 1e18;
const int MOD = 1e9 + 7;

mt19937 rnd(static_cast<unsigned int>(chrono::steady_clock().now().time_since_epoch().count()));

#define all(_x) _x.begin(), _x.end()
#define rall(_x) _x.rbegin(), _x.rend()
#define pb push_back
#define ff first
#define ss second
#define sz(_x) (int)_x.size()
#define display(_x)        \
    for (auto el : _x)     \
        cout << el << ' '; \
    cout << '\n'
#define cin_arr(_x)     \
    for (auto& el : _x) \
        cin >> el;
#define fast_input ios_base::sync_with_stdio(0); cin.tie(0)
#define setpr(_x) cout << setprecision(_x) << fixed
#define debug(x) cout << __FUNCTION__ << ": " << #x " = " << (x) << endl

const int MAXN = 1e5;
int n;
int used[MAXN];
set<pii> e;
vi g[MAXN];

// цвет 0 - не рассмотрели
// цвет 1 - лежит в независимом мн-ве
// цвет 2 - не лежит

void dfs(int v) {
    for (int u : g[v]) {
        // Если сосед уже лежит в нез. мн-ве, то нашу вершину взять нельзя
        if (used[u] == 1) {
            used[v] = 2;
        }
    }
    // Если все соседи не лежат, то наша лежит
    if (used[v] == 0) {
        used[v] = 1;
    }
 
    for (int u : g[v]) {
        if (!used[u]) {
            dfs(u);
        }
    }
}

void init() {
    int m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        v--;
        u--;
        e.insert({v, u});
        e.insert({u, v});
        g[v].pb(u);
        g[u].pb(v);
    }
}

vi guaranteed_solve() {
    while (!e.empty()) {
        auto [v, u] = *e.begin();
        used[v] = 1;
        used[u] = 1;

        for (int w : g[v]) {
            e.erase({v, w});
            e.erase({w, v});
        }

        for (int w : g[u]) {
            e.erase({u, w});
            e.erase({w, u});
        }
    }

    vi res;
    for (int i = 0; i < n; i++) {
        if (used[i] == 1) {
            res.pb(i);
        }
    }
    return res;
}

vi fast_solve(int is_random) {
    memset(used, 0, sizeof(int) * n);
    vi order(n);
    iota(all(order), 0);

    if (is_random) {
        shuffle(all(order), rnd);
    }

    for (int v : order) {
        if (!used[v]) {
            dfs(v);
        }
    }

    vi res;
    for (int i = 0; i < n; i++) {
        if (used[i] == 2) {
            res.pb(i);
        }
    }
    return res;
}

void print_ans(vi ans) {
    cout << sz(ans) << '\n';
    for (int v : ans) {
        cout << v + 1 << ' ';
    }
    cout << '\n';
}

void solve() {
    init();
    vi ans1 = guaranteed_solve();

    vi ans2 = fast_solve(0);
    for (int i = 0; i < (MAXN / n) * 10; i++) {
        vi ans3 = fast_solve(1);
        if (sz(ans3) < sz(ans2)) {
            swap(ans2, ans3);
        }
    }

    if (sz(ans1) <= sz(ans2)) {
        print_ans(ans1);
    } else {
        print_ans(ans2);
    }
}

int main() {
    fast_input;

#ifdef __APPLE__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    solve();
}
