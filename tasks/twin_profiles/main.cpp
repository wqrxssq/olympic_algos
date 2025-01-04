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
const int mod = 1e9 + 7;
const int mod2 = 1e9 + 11;
const int mod3 = 1e9 + 33;
const int mod4 = 1e9 + 9;
const double eps = 1e-9;

mt19937_64 rnd((int)chrono::steady_clock::now().time_since_epoch().count());

void solve() {
    int n, m;
    cin >> n >> m;
    vpii e(m);

    vll id(n), sets(n + (m << 1));
    for (int i = 0; i < n; i++) id[i] = rnd();

    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        v--;
        u--;
        sets[v] += id[u];
        sets[u] += id[v];
        e[i] = {v, u};
    }

    unordered_map<ll, ll> q;
    for (int i = 0; i < n; i++) q[sets[i]]++;

    ll ans = 0;
    for (auto x : q) ans += (x.second * (x.second - 1)) >> 1;
    for (int i = 0; i < m; i++)
        if (sets[e[i].first] - id[e[i].second] ==
            sets[e[i].second] - id[e[i].first])
            ans++;

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    solve();
}