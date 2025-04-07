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

const int MAXN = 305;
int n, m;
int can[MAXN][MAXN];

void do_move() {
    int old_can[MAXN][MAXN];
    for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j <= m + 1; j++) {
            old_can[i][j] = can[i][j];
        }
    }

    memset(can, 0, sizeof(can));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            can[i][j] = (old_can[i - 1][j] | old_can[i + 1][j] | old_can[i][j - 1] | old_can[i][j + 1]);
        }
    }
}

void print() {
    for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j <= m + 1; j++) {
            cout << can[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

void solve() {
    int q;
    cin >> n >> m >> q;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            can[i][j] = 1;
        }
    }

    for (int i = 0; i < q; i++) {
        int l1, l2, r1, r2;
        cin >> l1 >> l2 >> r1 >> r2;

        // cout << "Before move: " << '\n';
        // print();

        do_move();

        // cout << "After move: " << '\n';
        // print();

        for (int k = 0; k <= n + 1; k++) {
            for (int w = 0; w <= m + 1; w++) {
                can[k][w] &= (l1 <= k && k <= r1) && (l2 <= w && w <= r2);
            }
        }

        // cout << "After correlation: " << '\n';
        // print();
    }

    if (*max_element(*can, *can + (MAXN * MAXN)) == 1) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}

int main() {
    fast_input;
#ifdef __APPLE__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    solve();
    return 0;
}
