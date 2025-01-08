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
const int MAXA = 1e6;

int n;
int t[MAXA << 2];

void inc(int tl, int tr, int v, int pos) {
    if (tl == tr) {
        t[v]++;
    } else {
        int tm = (tl + tr) >> 1;
        if (pos <= tm) {
            inc(tl, tm, v << 1, pos);
        } else {
            inc(tm + 1, tr, v << 1 | 1, pos);
        }
        t[v] = t[v << 1] + t[v << 1 | 1];
    }
}

int find_kth(int tl, int tr, int v, int k) {
    if (tl == tr) {
        return tl;
    }
    int tm = (tl + tr) >> 1;
    if (k <= t[v << 1]) {
        return find_kth(tl, tm, v << 1, k);
    } else {
        return find_kth(tm + 1, tr, v << 1 | 1, k - t[v << 1]);
    }
}

void solve () {
    cin >> n;
    vi a(n);
    vi q(n);
    cin_arr(a);
    cin_arr(q);

    for (int i = 0; i < n; i++) {
        inc(0, MAXA - 1, 1, a[i] - 1);
        cout << find_kth(0, MAXA - 1, 1, q[i]) + 1 << '\n';
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
