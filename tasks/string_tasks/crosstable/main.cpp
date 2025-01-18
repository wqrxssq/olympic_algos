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

const int MAXN = 500;
const int MAXLEN = (MAXN * 2) * (MAXN * 2);
const int POWER = 31;
int n, m;
int k;
int a[MAXN][MAXN];
ll p[MAXLEN];

void clear(vvi& a) {
    for (int i = 0; i < n; i++) {
        a[i].assign(m, 0);
    }
}

void precalc() {
    p[0] = 1;
    for (int i = 1; i < MAXLEN; i++) {
        p[i] = 1LL * p[i - 1] * POWER;
    }
}

void add_string(ll &h, int i, int j, int len, int addi, int addj) {
    for (int k = 0; k < len; k++) {
        h *= POWER;
        h += a[i][j];
        i += addi + n;
        i %= n;
        j += addj + m;
        j %= m;
    }
}

ll binpow(ll a, int n) {
    if (n == 0) {
        return 1;
    }
    ll tmp = binpow(a, n >> 1);
    tmp *= tmp;
    if (n & 1) {
        tmp *= a;
    }
    return tmp;
}

ll binpow(ll h, int len, int n) {
    if (n == 1) {
        return h;
    }
    ll tmp = binpow(h, len, n >> 1);
    ll new_h = tmp * binpow(POWER, len * (n >> 1)) + tmp;

    if (n & 1) {
        new_h = new_h * p[len] + h;
    }
    return new_h;
}

void delete_char_and_add_char(ll &h, int len, int old_i, int old_j, int new_i, int new_j) {
    h -= a[old_i][old_j] * binpow(POWER, len - 1);
    h *= POWER;
    h += a[new_i][new_j];
}

void solve() {
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            a[i][j] = s[j] - 'a' + 1;
        }
    }

    precalc();
    unordered_map<ll, int> cnt;

    // right
    for (int i = 0; i < n; i++) {
        int period = m;
        ll h = 0;
        if (k < period) {
            add_string(h, i, 0, k, 0, 1);
        } else {
            add_string(h, i, 0, period, 0, 1);
            h = binpow(h, period, k / period);
            add_string(h, i, 0, k % period, 0, 1);
        }

        cnt[h]++;

        for (int j = 0; j < m - 1; j++) {
            delete_char_and_add_char(h, k, i, j, i, (j + k) % m);
            cnt[h]++;
        }
    }

    // left
    for (int i = 0; i < n; i++) {
        int period = m;
        ll h = 0;
        if (k < period) {
            add_string(h, i, m - 1, k, 0, -1);
        } else {
            add_string(h, i, m - 1, period, 0, -1);
            h = binpow(h, period, k / period);
            add_string(h, i, m - 1, k % period, 0, -1);
        }

        cnt[h]++;

        for (int j = m - 1; j > 0; j--) {
            delete_char_and_add_char(h, k, i, j, i, ((j - k) % m + m) % m);
            cnt[h]++;
        }
    }

    // down
    for (int j = 0; j < m; j++) {
        int period = n;
        ll h = 0;
        if (k < period) {
            add_string(h, 0, j, k, 1, 0);
        } else {
            add_string(h, 0, j, period, 1, 0);
            h = binpow(h, period, k / period);
            add_string(h, 0, j, k % period, 1, 0);
        }

        cnt[h]++;

        for (int i = 0; i < n - 1; i++) {
            delete_char_and_add_char(h, k, i, j, (i + k) % n, j);
            cnt[h]++;
        }
    }

    // up
    for (int j = 0; j < m; j++) {
        int period = n;
        ll h = 0;
        if (k < period) {
            add_string(h, n - 1, j, k, -1, 0);
        } else {
            add_string(h, n - 1, j, period, -1, 0);
            h = binpow(h, period, k / period);
            add_string(h, n - 1, j, k % period, -1, 0);
        }

        cnt[h]++;

        for (int i = n - 1; i > 0; i--) {
            delete_char_and_add_char(h, k, i, j, ((i - k) % n + n) % n, j);
            cnt[h]++;
        }
    }

    vvi used(n, vi(m));

    // right-down
    clear(used);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (used[i][j]) {
                continue;
            }
            int ii = i;
            int jj = j;
            used[ii][jj] = 1;
            int period = n * m / gcd(n, m);
            ll h = 0;
            if (k < period) {
                add_string(h, ii, jj, k, 1, 1);
            } else {
                add_string(h, ii, jj, period, 1, 1);
                h = binpow(h, period, k / period);
                add_string(h, ii, jj, k % period, 1, 1);
            }

            cnt[h]++;

            for (int z = 0; z < period - 1; z++) {
                delete_char_and_add_char(h, k, ii, jj, (ii + k) % n, (jj + k) % m);
                ii++;
                ii %= n;
                jj++;
                jj %= m;
                used[ii][jj] = 1;
                cnt[h]++;
            }
        }
    }

    // right-up
    clear(used);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (used[i][j]) {
                continue;
            }
            int ii = i;
            int jj = j;
            used[ii][jj] = 1;
            int period = n * m / gcd(n, m);
            ll h = 0;
            if (k < period) {
                add_string(h, ii, jj, k, -1, 1);
            } else {
                add_string(h, ii, jj, period, -1, 1);
                h = binpow(h, period, k / period);
                add_string(h, ii, jj, k % period, -1, 1);
            }

            cnt[h]++;

            for (int z = 0; z < period - 1; z++) {
                delete_char_and_add_char(h, k, ii, jj, ((ii - k) % n + n) % n, (jj + k) % m);
                ii += -1 + n;
                ii %= n;
                jj++;
                jj %= m;
                used[ii][jj] = 1;
                cnt[h]++;
            }
        }
    }

    // left-down
    clear(used);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (used[i][j]) {
                continue;
            }
            int ii = i;
            int jj = j;
            used[ii][jj] = 1;
            int period = n * m / gcd(n, m);
            ll h = 0;
            if (k < period) {
                add_string(h, ii, jj, k, 1, -1);
            } else {
                add_string(h, ii, jj, period, 1, -1);
                h = binpow(h, period, k / period);
                add_string(h, ii, jj, k % period, 1, -1);
            }

            cnt[h]++;

            for (int z = 0; z < period - 1; z++) {
                delete_char_and_add_char(h, k, ii, jj, (ii + k) % n, ((jj - k) % m + m) % m);
                ii++;
                ii %= n;
                jj += -1 + m;
                jj %= m;
                used[ii][jj] = 1;
                cnt[h]++;
            }
        }
    }

    // left-up
    clear(used);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (used[i][j]) {
                continue;
            }
            int ii = i;
            int jj = j;
            used[ii][jj] = 1;
            int period = n * m / gcd(n, m);
            ll h = 0;
            if (k < period) {
                add_string(h, ii, jj, k, -1, -1);
            } else {
                add_string(h, ii, jj, period, -1, -1);
                h = binpow(h, period, k / period);
                add_string(h, ii, jj, k % period, -1, -1);
            }

            cnt[h]++;

            for (int z = 0; z < period - 1; z++) {
                delete_char_and_add_char(h, k, ii, jj, ((ii - k) % n + n) % n, ((jj - k) % m + m) % m);
                ii += -1 + n;
                ii %= n;
                jj += -1 + m;
                jj %= m;
                used[ii][jj] = 1;
                cnt[h]++;
            }
        }
    }

    ll up = 0;
    ll down = 1LL * (n * m * 8) * (n * m * 8);

    for (auto [h, c] : cnt) {
        up += 1LL * c * c;
    }

    // cout << up << ' ' << down << '\n';

    ll gcd_up_down = gcd(up, down); 

    cout << up / gcd_up_down << "/" << down / gcd_up_down << '\n';
}


int main() {
    fast_input;
#ifdef __APPLE__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    solve();
}