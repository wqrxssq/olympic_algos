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

struct Node {
    int min, max, val;
};

const int MAXN = 1e5;
int n;
int a[MAXN];
Node t[MAXN << 2];

void push(Node &v, Node &l, Node &r) {
    if (v.val == 0) {
        return;
    }

    if (v.val <= l.max && v.val > l.min) {
        l.min = max(v.val, l.min);
        l.val = v.val;
    } else if (v.val > l.max) {
        l = {v.val, v.val, v.val};
    }

    if (v.val <= r.max && v.val > r.min) {
        r.min = max(v.val, r.min);
        r.val = v.val;
    } else if (v.val > r.max) {
        r = {v.val, v.val, v.val};
    }

    v.val = 0;
}

pll combine(pll l, pll r) {
    return {min(l.ff, r.ff), max(l.ss, r.ss)};
}
Node combine(Node l, Node r) {
    return {min(l.min, r.min), max(l.max, r.max), 0};
}

void build(int tl, int tr, int v) {
    if (tl == tr) {
        t[v] = {a[tl], a[tl], 0};
    } else {
        int tm = (tl + tr) >> 1;
        build(tl, tm, v << 1);
        build(tm + 1, tr, v << 1 | 1);
        t[v] = combine(t[v << 1], t[v << 1 | 1]);
    }
}

void set_max_x(int tl, int tr, int v, int l, int r, int x) {
    if (l > r) {
        return;
    }
    if (tl == l && tr == r) {
        if (x <= t[v].min) {
            return;
        }
        if (x <= t[v].max) {
            t[v].min = x;
            t[v].val = x;
        } else {
            t[v] = {x, x, x};
        }
    } else {
        int tm = (tl + tr) >> 1;
        push(t[v], t[v << 1], t[v << 1 | 1]);
        set_max_x(tl, tm, v << 1, l, min(tm, r), x);
        set_max_x(tm + 1, tr, v << 1 | 1, max(tm + 1, l), r, x);
        t[v] = combine(t[v << 1], t[v << 1 | 1]);
    }
}

pll min_max(int tl, int tr, int v, int l, int r) {
    if (l > r) {
        return {INF, 0};
    }
    if (tl == l && tr == r) {
        return {t[v].min, t[v].max};
    }
    push(t[v], t[v << 1], t[v << 1 | 1]);
    int tm = (tl + tr) >> 1;
    return combine(min_max(tl, tm, v << 1, l, min(tm, r)), 
            min_max(tm + 1, tr, v << 1 | 1, max(tm + 1, l), r));
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    build(0, n - 1, 1);

    int q;
    cin >> q;
    while (q--) {
        string s;
        cin >> s;
        if (s == "set") {
            int l, r, val;
            cin >> l >> r >> val;
            l--; r--;
            set_max_x(0, n - 1, 1, l, r, val);
        } else {
            int l, r;
            cin >> l >> r;
            l--; r--;
            pll ans = min_max(0, n - 1, 1, l, r);
            cout << ans.ss - ans.ff << '\n';
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
