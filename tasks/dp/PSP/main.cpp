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

const int MAXN = 20;
int n;
string sp[MAXN];

// Значение баланса для каждой строки
int last[MAXN];

unordered_map<int, vector<int>> q[MAXN];

// состояние - {маска, флаг был ли хоть один отрицательный префикс}
int dp[1 << MAXN][2];

void calc(int id) {
    // добавим все префиксы СП в мапу
    int balance = 0;
    for (int i = 0; i < sz(sp[id]); i++) {
        balance += (sp[id][i] == '(' ? 1 : -1);
        q[id][balance].push_back(i);
    }
    last[id] = balance;
}

int get_balance(int mask) {
    int balance = 0;
    for (int i = 0; i < n; i++) {
        balance += (mask & (1 << i) ? last[i] : 0);
    }
    return balance;
}

int f(int balance, int id) {
    // проверим, что при добавлении к маске id, не появится отрицательного префикса
    if (q[id].contains(-balance - 1)) {
        return -INF;
    } else {
        // найдем кол-во префиксов которые при присоединении новой строки даст 0
        return (q[id].contains(-balance) ? (int)q[id][-balance].size() : 0);
    }
}

int g(int balance, int id) {
    // проверим, что при добавлении к маске id, появится отриц. префикс
    if (!q[id].contains(-balance - 1)) {
        return -INF;
    } else {
        // найдем кол-во префиксов которые при присоединении новой строки даст 0, но идут до позиции с отриц. префиксом
        int i = q[id][-balance - 1][0];
        return (q[id].contains(-balance) ? lower_bound(q[id][-balance].begin(), q[id][-balance].end(), i) - q[id][-balance].begin() : 0);
    }
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> sp[i];
        calc(i);
    }

    dp[0][1] = -INF;

    for (int mask = 1; mask < (1 << n); mask++) {
        dp[mask][0] = -INF;
        dp[mask][1] = -INF;
        int balance = get_balance(mask);
        for (int from = 0; from < n; from++) {
            if (mask & (1 << from)) {
                balance -= last[from];

                dp[mask][0] = max(dp[mask][0], dp[mask ^ (1 << from)][0]
                    + f(balance, from));

                dp[mask][1] = max(dp[mask][1], dp[mask ^ (1 << from)][1]);
                dp[mask][1] = max(dp[mask][1], dp[mask ^ (1 << from)][0] 
                    + g(balance, from));

                balance += last[from];
            }
        }
    }
    cout << max(dp[(1 << n) - 1][0], dp[(1 << n) - 1][1]) << '\n';
}

int main() {
    fast_input;
#ifdef __APPLE__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    solve();
}
