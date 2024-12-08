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

const int MAXMASK = 1 << 30;
const int MAXN = 1e3;
int n;
int a[MAXN][MAXN];
int matrix[MAXN][MAXN];
int pref[MAXN][MAXN];

void build_matrix(uint mask) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = ((a[i][j] & mask) > 0);
        }
    }
}

int calc(int type) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            pref[i][j] = (matrix[i][j] != type ? 0 : 
                                (j == 0 ? 1 : pref[i][j - 1] + 1));
        }
    }
 
    ll res = 0;
    for (int j = 0; j < n; j++) {
        stack<pll> q;
        ll to_sum = 0;
        for (int i = 0; i < n; i++) {
            ll c = 0;
 
            while (q.size() != 0 && q.top().first > pref[i][j]) {
                to_sum -= (q.top().second + 1) * 
                             (q.top().first - pref[i][j]);
                c += q.top().second + 1;
                q.pop();
            }
 
            to_sum += pref[i][j];
            res = (res + to_sum) % MOD;
            q.push({pref[i][j], c});
        }
    }

    if (type == 0) {
        return ((1LL * n * (n + 1) * n * (n + 1)) / 
                    4 - res) % MOD;
    } else {
        return res % MOD;
    }
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    int sumOR = 0, sumAND = 0;
    for (uint mask = 1; mask <= MAXMASK; mask <<= 1) {
        build_matrix(mask);
        int tempOR = calc(0);
        int tempAND = calc(1);

        sumOR = (1LL * tempOR * mask + sumOR) % MOD;
        sumAND = (1LL * tempAND * mask + sumAND) % MOD;
    }
    cout << sumAND << ' ' << sumOR << '\n';
}

int main() {
    fast_input;
#ifdef __APPLE__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    solve();
}
