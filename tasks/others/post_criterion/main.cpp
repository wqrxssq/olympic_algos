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

const int MAXN = 1 << 10;

int my_log(int n) {
    return 31 - __builtin_clz(n);
}

bool is_less(int a, int b, int n) {
    for (int i = 0; i < n; i++) {
        if (((a & (1 << i)) > 0) > ((b & (1 << i)) > 0)) {
            return false;
        }
    }
    return true;
}
bool check_mono(vi& f, int n) {
    for (int mask1 = 0; mask1 < (1 << n); mask1++) {
        for (int mask2 = 0; mask2 < (1 << n); mask2++) {
            if (is_less(mask1, mask2, n)) {
                if (f[mask1] > f[mask2]) {
                    return false;
                }
            }
        }
    }
    return true;
}


bool is_good_poly(int mask, int val, vi& poly) {
    int res = 0;
    for (int i = 0; i < sz(poly); i++) {
        res ^= (poly[i] & ((mask & i) == i));
    }
    return res == val;
}
bool check_linear(vi& f, int n) {
    vi poly;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (is_good_poly(mask, f[mask], poly)) {
            poly.pb(0);
        } else {
            poly.pb(1);
        }

        if (poly[mask] == 1 && __builtin_popcount(mask) > 1) {
            return false;
        }
    }
    return true;
}

int reverse_mask(int mask, int n) {
    for (int i = 0; i < n; i++) {
        mask ^= (1 << i);
    }
    return mask;
}
bool check_selfdual(vi& f, int n) {
    for (int mask = 0; mask < (1 << n); mask++) {
        if (f[mask] == f[reverse_mask(mask, n)]) {
            return false;
        }
    }
    return true;
}

bool check_null_saving(vi &f, int n) {
    return f[0] == 0;
}

bool check_one_saving(vi &f, int n) {
    return f.back() == 1;
}

void solve() {
    string s1;
    getline(cin, s1);
    int m = stoi(s1);

    bool is_mono = 1;
    bool is_linear = 1;
    bool is_selfdual = 1;
    bool is_null_saving = 1;
    bool is_one_saving = 1;

    for (int i = 0; i < m; i++) {
        string s;
        getline(cin, s);
        vi f;
        for (int i = 0; i < sz(s); i += 2) {
            f.pb(s[i] == '1');
        }
        int n = my_log(sz(f));

        if (!check_mono(f, n)) {
            is_mono = 0;
        }
        if (!check_linear(f, n)) {
            is_linear = 0;
        }
        if (!check_selfdual(f, n)) {
            is_selfdual = 0;
        }
        if (!check_null_saving(f, n)) {
            is_null_saving = 0;
        }
        if (!check_one_saving(f, n)) {
            is_one_saving = 0;
        }
    }

    if (!is_mono && !is_linear && !is_selfdual && !is_null_saving && !is_one_saving) {
        cout << "COMPLETE\n";
        return;
    }
    if (is_mono) {
        cout << "MONOTONIC\n";
    }
    if (is_linear) {
        cout << "LINEAR\n";
    }
    if (is_selfdual) {
        cout << "SELF-DUAL\n";
    }
    if (is_null_saving) {
        cout << "0-PRESERVING\n";
    }
    if (is_one_saving) {
        cout << "1-PRESERVING\n";
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
