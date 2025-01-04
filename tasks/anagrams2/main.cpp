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
#include <tuple>
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

mt19937_64 rnd(static_cast<unsigned int>(chrono::steady_clock().now().time_since_epoch().count()));

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

const int MAXN = 1000;
int n, m;
int a[MAXN];
int b[MAXN];
unordered_map<int, ll> conv;

bool check(int k) {
    unordered_set<ll> h1;
    ll s = 0;
    for (int i = 0; i < k; i++) {
        s += conv[a[i]];
    }
    h1.insert(s);

    for (int i = k; i < n; i++) {
        s += conv[a[i]];
        s -= conv[a[i - k]];
        h1.insert(s);
    }

    s = 0;
    for (int i = 0; i < k; i++) {
        s += conv[b[i]];
    }

    if (h1.contains(s)) {
        return true;
    }

    for (int i = k; i < n; i++) {
        s += conv[b[i]];
        s -= conv[b[i - k]];
        if (h1.contains(s)) {
            return true;
        }
    }
    return false;
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (!conv.contains(a[i])) {
            conv[a[i]] = rnd();
        }
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> b[i];
        if (!conv.contains(b[i])) {
            conv[b[i]] = rnd();
        }
    }

    int res = 0;
    for (int i = 1; i <= min(n, m); i++) {
        if (check(i)) {
            res = i;
        }
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
