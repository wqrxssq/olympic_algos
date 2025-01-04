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

const int MAXN = 1e5;
const int N = 50;
int p, h;
int power[MAXN];

void precalc() {
    power[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        power[i] = (1LL * power[i - 1] * p) % MOD;
    }
}

void solve() {
    cin >> p >> h;
    precalc();

    int cnt = 100000;
    unordered_map<int, vi> q;
    for (int i = 0; i < cnt; i++) {
        vi a(N);
        int res = 0;
        for (int j = 0; j < N; j++) {
            a[j] = rnd() % 13 + 1; // [1, 13]
            res = (1LL * res * p + a[j]) % MOD;
        }
        q[res] = a;
    }

    for (auto [hash_s, a] : q) {
        int need = (1LL * h - hash_s + MOD) % MOD;
        if (q.contains(need)) {
            vi b = q[need];
            int res = 0;
            for (int i = 0; i < N; i++) {
                cout << char('a' + a[i] + b[i] - 1);
                res = (1LL * res * p + a[i] + b[i]) % MOD;
            }
            cout << '\n';
            assert(res == h);
            break;
        }
    }
}


int main() {
    fast_input;
#ifdef __APPLE__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    solve();
}
