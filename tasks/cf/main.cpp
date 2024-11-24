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

map <string, int> converter_name_v;

int p[MAXN];
vi g[MAXN];
int h[MAXN];

void dfs(int v, int pr = -1) {
    if (pr == -1) {
        h[v] = 0;
    } else {
        h[v] = h[pr] + 1; 
    }
    for (int u : g[v]) {
        if (u != pr) {
            dfs(u, v);
        }
    }
}

void solve() {
    cin >> n;

    memset(p, -1, sizeof(int) * MAXN);
    for (int i = 0; i < n - 1; i++) {
        string v, pr;
        cin >> v >> pr;
        if (!converter_name_v.count(v)) {
            converter_name_v[v] = sz(converter_name_v);
        }
        if (!converter_name_v.count(pr)) {
            converter_name_v[pr] = sz(converter_name_v);
        }

        g[converter_name_v[v]].pb(converter_name_v[pr]);
        g[converter_name_v[pr]].pb(converter_name_v[v]);

        p[converter_name_v[v]] = converter_name_v[pr];
    }

    for (int v = 0; v < n; v++) {
        if (p[v] == -1) {
            dfs(v);
        }
    }

    for (auto [s, v] : converter_name_v) {
        cout << s << ' ' << h[v] << '\n';
    }
}

int main() {
    fast_input;

#ifdef __APPLE__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    setpr(9);
    solve();
}
