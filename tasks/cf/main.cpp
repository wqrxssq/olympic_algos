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

struct two_deques {
    // инвариант размеры 2 дек примерно равны
    int size = 0;
    deque<int> L, R;

    void push(int value) {
        R.push_back(value);
        size++;
        if (size & 1) {
            L.push_back(R.front());
            R.pop_front();
        }
    }

    void push_middle(int value) {
        if (size & 1) {
            R.push_front(value);
        } else {
            L.push_back(value);
        }
        size++;
    }

    int get_first() {
        return L.front();
    }

    void pop_first() {
        L.pop_front();
        size--;
        if (size & 1) {
            L.push_back(R.front());
            R.pop_front();
        }
    }
};

const int MAXN = 5e5;

void solve() {
    int n;
    cin >> n;
    two_deques a;
    while (n--) {
        char c;
        cin >> c;
        if (c == '+') {
            int id;
            cin >> id;
            a.push(id);
        } else if (c == '*') {
            int id;
            cin >> id;
            a.push_middle(id);
        } else {
            int id = a.get_first();
            a.pop_first();
            cout << id << '\n';
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
