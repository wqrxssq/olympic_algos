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

const int MAXN = 2e5;
int n;
int H;

vi order;
int d[MAXN];
int t[MAXN << 2];
int h[MAXN];
int w[MAXN];

void build(int tl, int tr, int v) {
    if (tl == tr) {
        t[v] = d[tl];
    } else {
        int tm = (tl + tr) >> 1;
        build(tl, tm, v << 1);
        build(tm + 1, tr, v << 1 | 1);
        t[v] = max(t[v << 1], t[v << 1 | 1]);
    }
}

int query(int tl, int tr, int v, int l, int r) {
    if (l > r) {
        return 0;
    }
    if (tl == l && tr == r) {
        return t[v];
    }
    int tm = (tl + tr) >> 1;
    return max(query(tl, tm, v << 1, l, min(tm, r)), query(tm + 1, tr, v << 1 | 1, max(l, tm + 1), r));
}

void solve() {
    cin >> n >> H;
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }

    if (n == 1) {
        cout << 0 << '\n';
        return;
    }

    order.resize(n);
    iota(all(order), 0);

    sort(all(order), [&](int a, int b) {
        return h[a] < h[b] || (h[a] == h[b] && w[a] < w[b]);
    });

    for (int i = 0; i + 1 < n; i++) {
        d[i] = h[order[i + 1]] - h[order[i]];
    }
    build(0, n - 2, 1);

    int ans = INF;
    int cur_w = 0;
    for (int l = 0, r = 0; l < n; ++l) {
        while (r < n && cur_w < H) {
            cur_w += w[order[r]];
            ++r;
        }

        if (cur_w >= H && query(0, n - 2, 1, l, r - 2) < ans) {
            ans = query(0, n - 2, 1, l, r - 2);
        }

        cur_w -= w[order[l]];
    }

    cout << ans << '\n';
}

int main() {
    fast_input;
    solve();
}