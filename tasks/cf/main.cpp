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

struct cash_register {
    deque<int> *master, *fantom;
    // WARNING: fantom is reversed!
    cash_register() {
        master = new deque<int>();
        fantom = 0;
    }
    cash_register(deque<int>* mas) {
        master = mas;
        fantom = 0;
    }

    void push(int id) {
        id %= 10;
        if (!fantom) {
            master->push_back(id);
        } else {
            fantom->push_front(id);
            int n = fantom->size() + master->size();
            if (n & 1) {
                master->push_back(fantom->back());
                fantom->pop_back();
            }
        }
    }

    int front() {
        return master->front();
    }

    void pop() {
        master->pop_front();
        if (fantom) {
            int n = master->size() + fantom->size();
            if (n & 1) {
                master->push_back(fantom->back());
                fantom->pop_back();
            }
        }
    }

    void balance() {
        // master is bigger
        while (master->size() > fantom->size() + 1) {
            fantom->push_back(master->back());
            master->pop_back();
        }
        // fantom is bigger
        while (fantom->size() > master->size()) {
            master->push_back(fantom->back());
            fantom->pop_back();
        }
    }
};

void close_cash_register(cash_register& will_be_open, cash_register& will_be_close) {
    will_be_open.fantom = will_be_close.master;
    will_be_close.master = 0;
    will_be_open.balance();
}

void open_cash_register(cash_register& opened, cash_register& closed) {
    closed.master = opened.fantom;
    opened.fantom = 0;
}

void solve() {
    cash_register L, R;
    int q;
    cin >> q;
    int cur_id = 1;
    while (q--) {
        char type;
        cin >> type;
        if (type == 'a') {
            L.push(cur_id++);
        } else if (type == 'b') {
            R.push(cur_id++);
        } else if (type == 'A') {
            cout << L.front();
            L.pop();
        } else if (type == 'B') {
            cout << R.front();
            R.pop();
        } else if (type == '>') {
            close_cash_register(R, L);
        } else if (type == ']') {
            close_cash_register(L, R);
        } else if (type == '<') {
            open_cash_register(R, L);
        } else {
            open_cash_register(L, R);
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
