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
int n, k, first_x, second_x, a, b, c;

bool is_cyclic = false;
int ans[MAXK];

int find_max_element(int max_element) {
    int x0 = first_x;
    int x1 = second_x;
    int max_el = 0;
    for (int i = 0; i < n; i++) {
        int xn = (1LL * a * x0 + 1LL * b * x1 + c) & MAXMASK;

        if (xn == x0 && xn == x1) {
            is_cyclic = true;
        }

        x0 = x1;
        x1 = xn;
        if (xn <= max_element) {
            max_el = max(max_el, xn);
        }
    }

    return max_el;
}

int get_count(int min_can) {
    int cnt = 0;
    int x0 = first_x;
    int x1 = second_x;
    int max_el = 0;
    for (int i = 0; i < n; i++) {
        int xn = (1LL * a * x0 + 1LL * b * x1 + c) & MAXMASK;
        x0 = x1;
        x1 = xn;
        cnt += (xn >= min_can);
    }
    return cnt;
}

vi get_in(int l, int r) {
    vi temp;

    int x0 = first_x;
    int x1 = second_x;
    int max_el = 0;
    for (int i = 0; i < n; i++) {
        int xn = (1LL * a * x0 + 1LL * b * x1 + c) & MAXMASK;
        x0 = x1;
        x1 = xn;
        if (xn <= r && xn >= l) {
            temp.pb(xn);
        }
    }

    return temp;
}

void very_smart_solve() {
    vi temp;

    int x0 = first_x;
    int x1 = second_x;

    int cyclic_el = 0;
    for (int i = 0; i < n; i++) {
        int xn = (1LL * a * x0 + 1LL * b * x1 + c) & MAXMASK;

        if (xn == x0 && xn == x1) {
            cyclic_el = xn;
            break;
        }

        x0 = x1;
        x1 = xn;
        temp.pb(xn);
    }

    sort(all(temp));
    reverse(all(temp));

    int find_ = 0;
    for (int i = 0; i < temp.size(); i++) {
        if (temp[i] <= cyclic_el) {
            break;
        }
        cout << temp[i] << ' ';
        find_++;
    }
    while (find_ < k) {
        cout << cyclic_el << ' ';
        find_++;
    }
    cout << '\n';
}

void very_stupid_solve() {
    vi temp;
    int x0 = first_x;
    int x1 = second_x;
    for (int i = 0; i < n; i++) {
        int xn = (1LL * a * x0 + 1LL * b * x1 + c) & MAXMASK;
        x0 = x1;
        x1 = xn;
        temp.pb(xn);
    }
    sort(all(temp));
    reverse(all(temp));
    for (int i = 0; i < k; i++) {
        cout << temp[i] << ' ';
    }
    cout << '\n';
}

void solve() {
    cin >> n >> k >> first_x >> second_x >> a >> b >> c;

    int max_element = find_max_element(MAXMASK);

    if (is_cyclic) {
        very_smart_solve();
        return;
    }
    if (n <= MAXMEM) {
        very_stupid_solve();
        return;
    }

    int min_can = max(0, max_element - (max_element / n) * k * 4);
    int cnt_greater = get_count(min_can);

    assert(cnt_greater <= MAXMEM);

    vi a = get_in(min_can, max_element);

    sort(all(a));
    reverse(all(a));
    for (int i = 0; i < min(sz(a), k); i++) {
        ans[i] = a[i];
    }

    if (cnt_greater < k) {
        int max_element2 = find_max_element(a.back() - 1);
        int min_can2 = max(0, max_element2 - (max_element2 / n) * k * 10);

        vi b = get_in(min_can2, max_element2);
        sort(all(b));
        reverse(all(b));

        assert(sz(a) + sz(b) >= k);

        for (int i = sz(a); i < k; i++) {
            ans[i] = b[i - sz(b)];
        }
    }

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