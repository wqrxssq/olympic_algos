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

const int MAXN = 100;
int n, m;
int dp[MAXN + 1][MAXN + 1];
int l[MAXN], h[MAXN];
// dp[n][m] - минимальное кол-во блоков, чтобы из n первых ступеней сделать m

void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> h[i];
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = INF;
        }
    }
    dp[0][0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i; j > -1; j--) {
            int cur_height = 0;
            int need = 0;
            // переберем номер ступеньки на которой остановимся
            for (int k = i; k > -1; k--) {
                dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[k][j] + need);
                cur_height += h[k];
                need += cur_height * (k == 0 ? 0 : l[k - 1]);
            }
        }
    }
    cout << dp[n][m] << '\n';
}

int main() {
    fast_input;
    solve();
}