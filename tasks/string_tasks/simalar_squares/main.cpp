//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <math.h>

#include <algorithm>
#include <cassert>
#include <chrono>
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
using vll = vector<ll>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

const int INF = 1e9;
const ll INFLL = 1e18;
const int mod1 = 1e9 + 7;
const int mod2 = 1e9 + 11;
const int mod3 = 1e9 + 33;
const int mod4 = 1e9 + 9;
const double eps = 1e-9;

const int MAXN = 500;
const ll power_p = 585231, power_q = 531;
int n, m;
ll a[MAXN][MAXN];
ll p[MAXN], q[MAXN];
ll pref[MAXN + 1][MAXN + 1];

void init() {
    p[0] = 1;
    q[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        p[i] = p[i - 1] * power_p;
        q[i] = q[i - 1] * power_q;
    }
}

void get_2d_pref() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            pref[i + 1][j + 1] = pref[i][j + 1] * power_p +
                                 pref[i + 1][j] * power_q -
                                 pref[i][j] * power_p * power_q + a[i][j];
}

//[l1, r1) [l2, r2)
ll get_submatrix(int l1, int r1, int l2, int r2) {
    return pref[l2][r2] - pref[l1][r2] * p[l2 - l1] -
           pref[l2][r1] * q[r2 - r1] + pref[l1][r1] * p[l2 - l1] * q[r2 - r1];
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) a[i][j] = s[j] - 'a' + 1;
    }

    get_2d_pref();

    int l = 1, r = min(n, m);
    while (r - l > 1) {
        int ans_sz = 0;
        int x = (l + r) >> 1;
        unordered_set<ll> used;
        for (int i = 0; i <= n - x; i++)
            for (int j = 0; j <= m - x; j++) {
                ll submatrix = get_submatrix(i, j, i + x, j + x);
                if (used.count(submatrix)) {
                    ans_sz = x;
                } else {
                    used.insert(submatrix);
                }
            }
        if (ans_sz)
            l = x;
        else
            r = x - 1;
    }

    for (int sz = r; sz >= l; sz--) {
        unordered_map<ll, pii> used;
        for (int i = 0; i <= n - sz; i++)
            for (int j = 0; j <= m - sz; j++) {
                ll submatrix = get_submatrix(i, j, i + sz, j + sz);
                if (used.count(submatrix)) {
                    cout << sz << '\n';
                    cout << used[submatrix].first + 1 << ' '
                         << used[submatrix].second + 1 << '\n';
                    cout << i + 1 << ' ' << j + 1 << '\n';
                    exit(0);
                } else {
                    used[submatrix] = {i, j};
                }
            }
    }
    cout << 0 << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    init();
    solve();
}
