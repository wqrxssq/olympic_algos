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

vi operator *(vi a, vi b) {
    vi res(sz(a));
    for (int i = 0; i < sz(a); i++) {
        res[i] = a[b[i]];
    }
    return res;
}

vi pow(vi a, int n) {
    vi res = a;
    for (int i = 1; i < n; i++) {
        res = res * a;
    }
    return res;
}

vi rev(vi a) {
    vi res(sz(a));
    for (int i = 0; i < sz(a); i++) {
        res[a[i]] = i;
    }
    return res;
}

bool check(vi delta, vi p1, vi p2) {
    vi left = delta * p1 * delta;
    vi right = p2;
    return left == right;
}

void solve() {
    vi p1 = {7, 2, 6, 4, 1, 3, 5, 0};
    vi p2 = {6, 4, 0, 5, 2, 7, 1, 3};
    vi p3 = {3, 7, 0, 5, 2, 1, 6, 4};
    p2 = rev(p2);
    p3 = pow(p3, 15);
    p2 = p2 * p3;
    p2 = pow(p2, 166);

    vi ans(8);
    iota(all(ans), 0);

    do {
        if (check(ans, p1, p2)) {
            for (int i = 0; i < 8; i++) {
                cout << ans[i] + 1 << ' ';
            }
            cout << '\n';
        }
    } while (next_permutation(all(ans)));
}

int main() {
    fast_input;

#ifdef __APPLE__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    solve();
}
