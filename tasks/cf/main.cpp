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


struct Node {
    int x, min, max;
};
struct quer {
    stack<Node> out, in;

    int get_max(stack<Node>& s) {
        return (s.empty() ? -INF : s.top().max);
    }
    int get_min(stack<Node>& s) {
        return (s.empty() ? INF : s.top().min);
    }

    void push(int x) {
        in.push({x, min(get_min(in), x), max(get_max(in), x)});
    }

    void pop() {
        if (out.empty()) {
            while (!in.empty()) {
                int x = in.top().x;
                out.push({x, min(get_min(out), x), max(get_max(out), x)});
                in.pop();
            }
        }
        out.pop();
    }

    int get() {
        return max(get_max(in), get_max(out)) - min(get_min(in), get_min(out));
    }
};

const int MAXN = 6e5;
int n;
int a[MAXN];

pair<int, int> query(int m) {
    int max_len = 0;
    int L = 0, R = 0;
    quer q;
    for (int l = 0, r = 0; l < n; l++) {
        while (r < n && q.get() <= m) {
            q.push(a[r++]);
        }
        if (r - l >= max_len) {
            L = l + 1;
            R = (q.get() <= m ? r : r - 1);
            max_len = r - l;
        }
        q.pop();
    }
    return {L, R};
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int q;
    cin >> q;
    while (q--) {
        int m;
        cin >> m;
        auto [l, r] = query(m);
        cout << l << ' ' << r << '\n';
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
