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
const int MOD1 = 1e9 + 7;
const int MOD2 = 1e9 + 9;

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
const int POWER1 = 31;
const int POWER2 = 51;

int n;
string s;

vector<int> precalc(int mod, int power) {
    vector <int> powers(n + 1);
    powers[0] = 1;
    for (int i = 0; i < n; i++) {
        powers[i + 1] = (1LL * powers[i] * power) % mod;
    }
    return powers;
}

vector<int> build(int mod, int power) {
    vector<int> pref(n + 1);
    for (int i = 0; i < n; i++) {
        pref[i + 1] = (1LL * pref[i] * power + (s[i] - 'a' + 1)) % mod;
    }
    return pref;
}

int get_hash(int l, int r, vector<int>& pref, vector<int>& p, int mod) { // [l, r)
    return (((1LL * pref[r] - 1LL * pref[l] * p[r - l]) % mod) + mod) % mod;
} 

bool cmp(int l1, int r1, int l2, int r2, vector<int>& pref, vector<int>& powers, int mod) { // [l1, r1), [l2, r2)
    int l = 0, r = min(r2 - l2, r1 - l1) + 1;
    // l is same
    // r is not same
    while (r - l > 1) {
        int m = (l + r) >> 1;
        if (get_hash(l1, l1 + m, pref, powers, mod) == get_hash(l2, l2 + m, pref, powers, mod)) {
            l = m;
        } else {
            r = m;
        }
    }
    if (l == min(r2 - l2, r1 - l1)) {
        return (r1 - l1) < (r2 - l2);
    }
    return s[l1 + l] < s[l2 + l];
}

void solve () {
    cin >> s;
    n = sz(s);

    vector<int> precalc_powers1 = precalc(MOD1, POWER1);
    vector<int> pref1 = build(MOD1, POWER1);

    int q;
    cin >> q;
    while (q--) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        l1--; l2--;
        if (cmp(l1, r1, l2, r2, pref1, precalc_powers1, MOD1)) {
            cout << "<\n";
        } else if (cmp(l2, r2, l1, r1, pref1, precalc_powers1, MOD1)) {
            cout << ">\n";
        } else {
            cout << "=\n";
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
