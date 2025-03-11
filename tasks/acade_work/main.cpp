#pragma GCC optimize("O3,unroll-loops")

#include <iostream>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <queue>
#include <math.h>
#include <vector>
#include <string>
#include <stack>
#include <cassert>
#include <random>
#include <chrono>
#include <cstring>
#include <iomanip>
using namespace std;

#define all(_x) _x.begin(), _x.end()
#define rall(_x) _x.rbegin(), _x.rend()
#define pb push_back
#define sz(_x) (int)_x.size()
#define ff first
#define ss second
#define cin_arr(a)for (int _ii = 0; _ii < (int)a.size(); _ii++)  \
    cin >> a[_ii];
#define display(a) for (auto _ii : a)                            \
    cout << _ii << ' ';                                          \
cout << '\n';
#define display_pairs(a) for (auto _ii : a)                      \
    cout << _ii.ff << ' ' << _ii.ss << '\n';
#define display_matrix(a) for (auto _row : a)                    \
{                                                                \
    for (auto _cell : _row)                                      \
        cout << _cell << ' ';                                    \
    cout << '\n';                                                \
}                                                                \
cout << '\n'
#define fast_input ios_base::sync_with_stdio(0); cin.tie(0)
#define fast_interactive_input ios_base::sync_with_stdio(0)

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> pii;
typedef pair <ll, ll> pll;
typedef vector <pii> vpii;
typedef vector <vi> vvi;

const int INF = 1e9;
const ll INFLL = 1e18;
const int mod = 1e9 + 7;
const double eps = 1e-6;

const int MAXN = 20;
int n;
ll a[1 << MAXN];
ll dp[1 << MAXN][MAXN + 1];
ll f[1 << MAXN];

void solve() {
    cin >> n;
    for (int i = 0; i < (1 << n); i++) {
        cin >> f[i];
    }

    for (int mask = 0; mask < (1 << n); mask++) {
        dp[mask][0] = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                dp[mask][i + 1] = dp[mask][i] + dp[mask ^ (1 << i)][i];
            } else {
                dp[mask][i + 1] = dp[mask][i];
            }
        }
        a[mask] = f[mask] - dp[mask][n];

        dp[mask][0] = a[mask];
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                dp[mask][i + 1] = dp[mask][i] + dp[mask ^ (1 << i)][i];
            } else {
                dp[mask][i + 1] = dp[mask][i];
            }
        }
    }

    for (int i = 0; i < (1 << n); i++) {
        cout << a[i] << ' ';
    }
    cout << '\n';
}

int main() {
    fast_input;
    solve();
}
