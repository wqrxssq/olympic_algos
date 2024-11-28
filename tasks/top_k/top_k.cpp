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

const int MAXN = 1e8;
const int MAXK = 200000;
const int MAXMEM = 1e6;
const int MAXMASK = (1 << 31) - 1;
const int INTERVAL = 2148;

int cnt[MAXMEM];
int n, k, first_x, second_x, a, b, c;
int ans[MAXK];

void get_cnt() {
    int x0 = first_x;
    int x1 = second_x;
    for (int i = 0; i < n; i++) {
        int xn = (1LL * a * x0 + 1LL * b * x1 + c) & MAXMASK;

        ++cnt[xn / INTERVAL];

        x0 = x1;
        x1 = xn;
    }
}

int get_some_ans(unsigned int L) {
    vi el;

    int x0 = first_x;
    int x1 = second_x;
    for (int i = 0; i < n; i++) {
        int xn = (1LL * a * x0 + 1LL * b * x1 + c) & MAXMASK;

        if ((unsigned int)xn >= L) {
            el.pb(xn);
        }

        x0 = x1;
        x1 = xn;
    }

    sort(rall(el));
    for (int i = 0; i < sz(el); i++) {
        ans[i] = el[i];
    }
    return sz(el);
}

void get_other_in_busket(int id_busket, int l) {
    int new_cnt[INTERVAL] = {0};
    unsigned int L = 1LL * id_busket * INTERVAL;
    unsigned int R = 1LL * (id_busket + 1) * INTERVAL;

    int x0 = first_x;
    int x1 = second_x;
    for (int i = 0; i < n; i++) {
        int xn = (1LL * a * x0 + 1LL * b * x1 + c) & MAXMASK;

        if ((unsigned int)xn >= L && (unsigned int)xn < R) {
            ++new_cnt[xn - L];
        }

        x0 = x1;
        x1 = xn;
    }

    for (int i = INTERVAL - 1; l < k; i--) {
        for (int j = 0; j < new_cnt[i] && l < k; j++) {
            ans[l++] = i + L;
        }
    }
}

void solve() {
    cin >> n >> k >> first_x >> second_x >> a >> b >> c;

    // if (n <= MAXMEM) {
    //     very_stupid_solve();
    //     return;
    // }

    get_cnt();
    int ind_min_busket = -1;
    int need = k;
    for (int i = MAXMEM - 1; need > 0; i--) {
        need -= cnt[i];
        if (need <= 0) {
            ind_min_busket = i;
        }
    }

    unsigned int L = 1LL * (ind_min_busket + 1) * INTERVAL;
    int cnt_gettet = get_some_ans(L);
    get_other_in_busket(ind_min_busket, cnt_gettet);

    for (int i = 0; i < k; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}

int main() {
    fast_input;

#ifdef __APPLE__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    solve();
}