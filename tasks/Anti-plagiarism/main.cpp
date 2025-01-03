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

using uint = unsigned int;
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
const int MOD1 = 1e9 + 7;
const int MOD2 = 1e9 + 9;

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
vi g[MAXN];
ll c[MAXN];

ll h_tree[MAXN];
ll h_tree2[MAXN];

ll f(ll x){
    return ((x * x * 51) ^ x) * 31 + 126431;
}
ll h(ll x) {
    return ((541 * x) ^ (13 * x + 31)) + 12532693;
}

void dfs(int v, int p = -1) {
    for (int u : g[v]) {
        if (u != p) {
            dfs(u, v);
            h_tree[v] += f(h_tree[u]);
            h_tree2[v] += h(h_tree2[u]);
        }
    }
    h_tree[v] += f(c[v]);
    h_tree2[v] += h(c[v]);
}

void solve () {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int v, u;
        cin >> v >> u;
        v--; u--;
        g[v].pb(u);
        g[u].pb(v);
    }

    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    dfs(0);

    map<pair<ll, ll>, int> q;
    for (int v = 0; v < n; v++) {
        q[{h_tree[v], h_tree2[v]}]++;
    }

    ll ans = 0;
    for (auto [w, cnt] : q) {
        ans += (1LL * cnt * (cnt - 1)) / 2;
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
