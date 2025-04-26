#pragma GCC optimize("O3,unroll-loops")

#include <math.h>

#include <algorithm>
#include <array>
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
using pll = pair<ll, ll>;
using vpii = vector<pii>;
using ld = long double;

const double EPS = 1e-9;
const double PI = acos(-1);
const int INF = 1e9;
const ll INFLL = 1e18;
const int MOD = 1e9 + 7;

#define all(_x) _x.begin(), _x.end()
#define sz(_x) _x.size()
#define rall(_x) _x.rbegin(), _x.rend()
#define pb push_back
#define ff first
#define ss second
#define display(_x)                       \
    for (auto el : _x) cout << el << ' '; \
    cout << '\n'
#define cin_arr(_x) \
    for (auto &el : _x) cin >> el;
#define fast_input ios_base::sync_with_stdio(0); cin.tie(nullptr)
#define setpr cout << setprecision(9) << fixed

struct r {
    int x, y;
};
istream& operator>>(istream &in, r &p) { 
    in >> p.x >> p.y;
    return in;
}
r operator +(r a, r b) {
    return {a.x + b.x, a.y + b.y};
}
r operator -(r a, r b) {
    return {a.x - b.x, a.y - b.y};
}
double angle(r a) {
    return atan2(a.y, a.x);
}

const int MAXN = 2000;
int n;
r p[MAXN];
double w[MAXN];

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int cur = 0;
        for (int j = 0; j < n; j++) {
            if (j != i) {
                w[cur++] = angle(p[j] - p[i]);
            }
        }
        sort(w, w + cur);
        for (int j = 0, k = 1; j < cur && w[j] <= 0; j++) {
            while (k < cur && w[k] - w[j] < PI) {
                k++;
            }
            ll x = (k - j - 1);
            ll y = n - 2 - x;
            ans += x * (x - 1) / 2 * y * (y - 1) / 2;
        }
    }
    cout << ans << endl;
}

int main() {
    fast_input;
    setpr;
#ifdef __APPLE__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    solve();
    return 0;
}
