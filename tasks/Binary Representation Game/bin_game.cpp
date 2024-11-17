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

const int MAXN = 52;
const int MAXTRIES = 1e7;
int n;
int p[MAXN][MAXN];

int calc(int pos, int iteration = 0) {
    if (pos == n) {
        return 1;
    }
    if (pos == n + 1 || iteration == 100) {
        return 0;
    }

    int go = rnd() % 100;
    for (int i = 0; i < n + 2; i++) {
        if (go < p[pos][i]) {
            return calc(i, iteration + 1);
        }
        go -= p[pos][i];
    }
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 2; j++) {
            cin >> p[i][j];
        }
    }

    int is_good = 0;
    for (int i = 0; i < MAXTRIES; i++) {
        is_good += calc(0);
    }

    cout << (long double)is_good / MAXTRIES << '\n';
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