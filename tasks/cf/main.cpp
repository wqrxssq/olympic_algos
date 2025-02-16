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
int a[MAXN];
int b[MAXN];
ll pref[MAXN + 1];
pll t[MAXN << 2];

void build_pref() {
    for (int i = 0; i < n; i++) {
        pref[i + 1] = pref[i] + b[i];
    }
}

// [l, r)
ll sum(int l, int r) {
    return pref[r] - pref[l];
}

pll merge(pll v, pll vl, pll vr, int tl, int tr) {
    return {vl.ff + vr.ff + sum(tl, tr + 1) * v.ss, v.ss};
}

void build(int tl, int tr, int v) {
    if (tl == tr) {
        t[v] = {a[tl], 0};
    } else {
        int tm = (tl + tr) >> 1;
        build(tl, tm, v << 1);
        build(tm + 1, tr, v << 1 | 1);
        t[v].ff = t[v << 1].ff + t[v << 1 | 1].ff;
    }
}

void add(int tl, int tr, int v, int l, int r) {
    if (l > r) {
        return;
    }
    if (tl == l && tr == r) {
        t[v].ff += sum(l, r + 1);
        t[v].ss++;
    } else {
        int tm = (tl + tr) >> 1;
        add(tl, tm, v << 1, l, min(tm, r));
        add(tm + 1, tr, v << 1 | 1, max(tm + 1, l), r);
        t[v] = merge(t[v], t[v << 1], t[v << 1 | 1], tl, tr);
    }
}

ll query(int tl, int tr, int v, int l, int r) {
    if (l > r) {
        return 0;
    }
    if (tl == l && tr == r) {
        return t[v].ff;
    }
    int tm = (tl + tr) >> 1;
    return query(tl, tm, v << 1, l, min(tm, r)) + query(tm + 1, tr, v << 1 | 1, max(tm + 1, l), r) + sum(l, r + 1) * t[v].ss;
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    build_pref();
    build(0, n - 1, 1);

    int q;
    cin >> q;
    while (q--) {
        char c;
        int l, r;
        cin >> c >> l >> r;
        if (c == '+') {
            add(0, n - 1, 1, l, r);
        } else {
            cout << query(0, n - 1, 1, l, r) << '\n';
        }
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
