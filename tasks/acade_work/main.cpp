#include <math.h>

#include <algorithm>
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
using namespace std;

using ll = long long;
using ull = unsigned long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vll = vector<ll>;
using pii = pair<int, int>;
using vpii = vector<pii>;

const double eps = 0.0001;
const int INF = 1e9;
const ll INFLL = 1e18;
const int MOD = 1e9 + 7;

#define all(_x) _x.begin(), _x.end()
#define rall(_x) _x.rbegin(), _x.rend()
#define pb push_back
#define ff first
#define ss second
#define sz(_x) (int)_x.size()
#define display(_x)                       \
    for (auto el : _x) cout << el << ' '; \
    cout << '\n'
#define cin_arr(_x) \
    for (auto &el : _x) cin >> el;
#define fast_input ios_base::sync_with_stdio(0)
#define setpr cout << setprecision(6) << fixed

const int MAXN = 20;
int w[MAXN];
int dp[1 << MAXN];

void solve() {
    memset(dp, -1, sizeof(dp));

    int S = 0;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> w[i];
        S += w[i];
    }

    if (S % 3 != 0) {
        cout << "No solution\n";
        return;
    }
    S /= 3;

    dp[0] = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if ((mask & (1 << i)) == 0 && dp[mask ^ (1 << i)] == -1 && dp[mask] != -1 && dp[mask] + w[i] <= S) {
                dp[mask ^ (1 << i)] = (dp[mask] + w[i]) % S;
            }
        }
    }
    cout << dp[(1 << n) - 1] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
