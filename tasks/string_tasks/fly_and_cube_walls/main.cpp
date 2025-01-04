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
#include <tuple>
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
const int MOD1 = 1e9 + 7;
const int MOD2 = 1e9 + 9;

mt19937_64 rnd(static_cast<unsigned int>(chrono::steady_clock().now().time_since_epoch().count()));

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

const int MAXN = 2e5;
int a[MAXN];
int b[MAXN];

vi prefix_function(vi a) {
    vi p(sz(a));
    for (int i = 1; i < sz(a); i++) {
        int j = p[i - 1];
        while (j && a[j] != a[i]) {
            j = p[j - 1];
        }
        if (a[j] == a[i]) {
            j++;
        }
        p[i] = j;
    }
    return p;
}

void solve() {
    int n, w;
    cin >> n >> w;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < w; i++) {
        cin >> b[i];
    }

    vi text(n - 1);
    for (int i = 1; i < n; i++) {
        text[i - 1] = a[i] - a[i - 1];
    }
    vi s(w - 1);
    for (int i = 1; i < w; i++) {
        s[i - 1] = b[i] - b[i - 1];
    }

    s.push_back(2 * INF);
    s.insert(s.end(), all(text));

    vi p = prefix_function(s);

    int ans = 0;
    for (int x : p) {
        if (x == w - 1) {
            ans++;
        }
    }
    cout << ans << '\n';
}

int main() {
    fast_input;
#ifdef __APPLE__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    solve();
}
