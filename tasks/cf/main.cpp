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

const int MAXMASK = 1 << 30;
const int MAXN = 3;
int n;
int a[MAXN][MAXN];
int AND[MAXN][MAXN];
int OR[MAXN][MAXN];

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    int sumOR = 0, sumAND = 0;
    for (uint mask = 1; mask <= MAXMASK; mask <<= 1) {
        memset(OR, 0, sizeof(int) * MAXN * MAXN);
        memset(AND, 0, sizeof(int) * MAXN * MAXN);

        OR[0][0] = (a[0][0] & mask ? 1 : 0);
        for (int i = 1; i < n; i++) {
            OR[0][i] = (a[0][i] & mask ? i + 1 : OR[0][i - 1]);
            OR[i][0] = (a[i][0] & mask ? i + 1 : OR[i - 1][0]);
        }

        for (int i = 1; i < n; i++) {
            for (int j = 1; j < n; j++) {
                if (a[i][j] & mask) {
                    OR[i][j] = (i + 1) * (j + 1);
                } else {
                    OR[i][j] = OR[i - 1][j] + OR[i][j - 1] - OR[i - 1][j - 1];
                }
            }
        }

        int tempOR = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                tempOR = (tempOR + OR[i][j]) % MOD;
            }
        }
        tempOR = (1LL * tempOR * mask) % MOD;
        sumOR += tempOR;
    }
    cout << sumOR << '\n';
}

int main() {
    fast_input;
#ifdef __APPLE__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    solve();
}
