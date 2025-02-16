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

const int power = 31;
const int MAXN = 1e5;
int n;
ll p[MAXN];
pll t[MAXN << 2];
string s;

void init() {
    p[0] = 1;
    for (int i = 1; i < n; i++) {
        p[i] = p[i - 1] * power;
    }
}

void build(int tl, int tr, int v) {
    if (tl == tr) {
        t[v] = {s[tl] - 'a' + 1, s[tl] - 'a' + 1};
    } else {
        int tm = (tl + tr) >> 1;
        build(tl, tm, v << 1);
        build(tm + 1, tr, v << 1 | 1);
        t[v] = {t[v << 1].ff * p[tr - tm] + t[v << 1 | 1].ff,
               t[v << 1].ss + t[v << 1 | 1].ss * p[tm - tl + 1]};
    }
}

void change(int tl, int tr, int v, int pos, int val) {
    if (tl == tr) {
        t[v] = {val, val};
    } else {
        int tm = (tl + tr) >> 1;
        if (pos <= tm) {
            change(tl, tm, v << 1, pos, val);
        } else {
            change(tm + 1, tr, v << 1 | 1, pos, val);
        }
        t[v] = {t[v << 1].ff * p[tr - tm] + t[v << 1 | 1].ff,
               t[v << 1].ss + t[v << 1 | 1].ss * p[tm - tl + 1]};
    }
}

pll get_hashes(int tl, int tr, int v, int l, int r) {
    if (tl == l && tr == r) {
        return t[v];
    }
    int tm = (tl + tr) >> 1;
    if (r <= tm) {
        return get_hashes(tl, tm, v << 1, l, r);
    }
    if (l > tm) {
        return get_hashes(tm + 1, tr, v << 1 | 1, l, r);
    }
    pll hl = get_hashes(tl, tm, v << 1, l, tm);
    pll hr = get_hashes(tm + 1, tr, v << 1 | 1, tm + 1, r);
    return {hl.ff * p[r - tm] + hr.ff, 
            hl.ss + hr.ss * p[tm - l + 1]};
}

void solve() {
    cin >> s;
    n = sz(s);

    init();
    build(0, n - 1, 1);

    int q;
    cin >> q;
    while (q--) {
        string m;
        cin >> m;
        if (m == "palindrome?") {
            int l, r;
            cin >> l >> r;
            l--; r--;
            pll h = get_hashes(0, n - 1, 1, l, r);
            if (h.ff == h.ss) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        } else {
            int pos;
            char c;
            cin >> pos >> c;
            pos--;
            change(0, n - 1, 1, pos, c - 'a' + 1);
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
