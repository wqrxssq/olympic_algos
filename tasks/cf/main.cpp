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

const int MAXN = 5e5;
int n;
int a[MAXN];
vi g[MAXN];
ll dp[MAXN][2];

vi ans;
void get_ans(int v, bool status, int p = -1) {
    if (status) {
        ans.pb(v + 1);
    }

    for (int u : g[v]) {
        if (u == p) {
            continue;
        }
        if (status) {
            get_ans(u, dp[u][1] < dp[u][0], v);
        } else {
            get_ans(u, 1, v);
        }
    }
}

void dfs(int v, int p = -1) {
    for (int u : g[v]) {
        if (u == p) {
            continue;
        }
        dfs(u, v);
        dp[v][0] += dp[u][1];
        dp[v][1] += min(dp[u][0], dp[u][1]);
    }
    dp[v][1] += a[v];
}

void solve() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int v, u;
        cin >> v >> u;
        v--; u--;
        g[v].pb(u);
        g[u].pb(v);
    }

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    dfs(0);

    if (n == 1) {
        cout << dp[0][1] << " 1\n1\n";
    } else {
        bool status = dp[0][0] > dp[0][1];
        cout << min(dp[0][0], dp[0][1]) << ' ';
        get_ans(0, status);
        cout << sz(ans) << '\n';
        for (int v : ans) {
            cout << v << ' ';
        }
        cout << '\n';
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
