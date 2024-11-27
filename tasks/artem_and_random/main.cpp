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

const int MAXN = 1e5;
double mn[MAXN], mx[MAXN];
double a[MAXN], b[MAXN];

void solve() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> mx[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> mn[i];
    }

    double pref1 = 0, pref2 = 0;
    for (int i = 0; i < n; i++) {
        double A, B, C;
        double c = mx[i] + mn[i] ;
        A = -1;
        B = pref2 - pref1 + c;
        C = pref1 * c - mx[i];
        double D = max(0.0, B * B - 4 * A * C);
        D = sqrt(D);
        if (c - abs((-B + D) / (2 * A)) > -EPS)
            a[i] = abs((-B + D) / (2 * A));
        else
            a[i] = (-B - D) / (2 * A);
        b[i] = c - a[i];
        pref1 += a[i];
        pref2 += b[i];
    }

    for (int i = 0; i < n; ++i) {
        cout << a[i] << " ";
    }
    cout << '\n';
    for (int i = 0; i < n; ++i) {
        cout << b[i] << " ";
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
