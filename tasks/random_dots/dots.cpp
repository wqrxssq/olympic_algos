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

const unsigned int X = 1e8;
const unsigned int A = 134775813;
const unsigned int C = 1;
const ll M = (1LL << 32);
const unsigned int MAXSEED = 4294967295;
unsigned int seed;

void solve() {
    unsigned int a1, a2;
    cin >> a1 >> a2;
    int c = 0;

    int need_seed_l = (1LL * a1 * M) / X;
    int need_seed_r = need_seed_l + 50;
    cout << need_seed_l << '\n'; 

    for (unsigned int s0 = 0; s0 <= MAXSEED; s0++) {
        seed = s0;

        seed = (A * seed + C);
        unsigned int x = (1LL * seed * X) / M;
        
        if (x == a1) {
            cout << seed << ' ';
            c = s0;
            seed = (A * seed + C);
            x = (1LL * seed * X) / M;
            // if (x == a2) {
            //     cout << s0 << ' ';
            // }
        }
        if (s0 == MAXSEED) {
            break;
        }
    }
    cout << '\n';
}

int main() {
    fast_input;

#ifdef __APPLE__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    setpr(9);
    solve();
}
