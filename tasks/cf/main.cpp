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

const int MAXN = 1e6;
int n;
int mod;

bool is_acyclic;
vi g[MAXN];
int used[MAXN];

vi comp;
int d[MAXN];
vi path;

int fact[MAXN + 1];

void init() {
    fact[0] = 1;
    for (int i = 1; i <= MAXN; i++) {
        fact[i] = (1LL * fact[i - 1] * i) % mod;
    }
}

void dfs(int v, int p = -1) {
    used[v] = 1;
    for (int u : g[v]) {
        if (u == p) {
            continue;
        }
        if (used[u]) {
            is_acyclic = false;
            return;
        }
        dfs(u, v);
    }
}

void bfs(int v, int p = -1) {
    d[v] = (p == -1 ? 0 : d[p] + 1);
    for (int u : g[v]) {
        if (u == p) {
            continue;
        }
        bfs(u, v);
    }
}


bool find_path(int v, int u, int p = -1) {
    if (v == u) {
        return true;
    }
    for (int w : g[v]) {
        if (w == p) {
            continue;
        }
        if (find_path(w, u, v)) {
            path.pb(w);
            return true;
        }
    }
    return false;
}

void get_comp(int v, int p = -1) {
    for (int u : g[v]) {
        if (u != p) {
            get_comp(u, v);
        }
    }
    comp.pb(v);
}

vi find_diametr(int v) {
    comp.clear();
    get_comp(v);
    bfs(v);

    int u = v;
    for (int x : comp) {
        if (d[x] > d[u]) {
            u = x;
        }
    }
    bfs(u);

    int w = u;
    for (int x : comp) {
        if (d[x] > d[w]) {
            w = x;
        }
    }
    path.clear();
    find_path(u, w);
    path.pb(u);
    return path;
}

int calc(vi& diametr) {
    int ans = 1;
    for (int i = 1; i < sz(diametr) - 1; i++) {
        int cnt = 0;
        for (int u : g[diametr[i]]) {
            if (u == diametr[0] || u == diametr.back()) {
                cnt++;
            } else if (u != diametr[i - 1] && u != diametr[i + 1]) {
                if (sz(g[u]) != 1) {
                    ans = 0;
                }
                cnt++;
            }
        }
        ans = (1LL * ans * fact[cnt]) % mod;
    }
    if (sz(diametr) <= 3) {
        return ans;
    } else {
        return (ans * 2) % mod;
    }
}

void solve() {
    int m;
    cin >> n >> m >> mod;

    init();

    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        v--;
        u--;
        g[v].pb(u);
        g[u].pb(v);
    }

    int ans = 1;
    int cnt_other_comp = 0;
    int cnt_comp_1 = 0;
    int cnt_other = 2;

    for (int v = 0; v < n; v++) {
        if (sz(g[v]) == 0) {
            cnt_comp_1++;
        } else {
            cnt_other++;
            if (!used[v]) {
                cnt_other_comp++;
                is_acyclic = true;
                dfs(v);
                if (!is_acyclic) {
                    ans = 0;
                    break;
                }
                vi diametr = find_diametr(v);
                ans = (1LL * calc(diametr) * 2 * ans) % mod;
            }
        }
    }

    ans = (1LL * ans * fact[cnt_other_comp]) % mod;

    for (int i = 0; i < cnt_comp_1; i++) {
        ans = (1LL * ans * (cnt_other + i)) % mod;
    }

    cout << ans << '\n';
}

int main() {
    fast_input;

#ifdef __APPLE__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    solve();
}
