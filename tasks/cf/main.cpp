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

struct node {
    node *l = 0, *r = 0;
    int key;

    node(int x) : key(x) {}

    void add(int x) {
        node* v = this;
        while (v) {
            if (x < v->key) {
                if (!v->l) {
                    v->l = new node(x);
                    cout << "DONE\n";
                    return;
                } else {
                    v = v->l;
                }
            } else if (x > v->key) {
                if (!v->r) {
                    v->r = new node(x);
                    cout << "DONE\n";
                    return;
                } else {
                    v = v->r;
                }
            } else {
                cout << "ALREADY\n";
                return;
            }
        }
    }

    bool search(int x) {
        node* v = this;
        while (v && v->key != x) {
            if (x < v->key) {
                v = v->l;
            } else if (x > v->key) {
                v = v->r;
            }
        }
        return (v && v->key == x);
    }

    void print_tree(int deep = 0) {
        if (l) {
            l->print_tree(deep + 1);
        }
        for (int i = 0; i < deep; i++) {
            cout << '.';
        }
        cout << key << '\n';
        if (r) {
            r->print_tree(deep + 1);
        }
    }
};

node* root;

void solve() {
    string type;
    while (cin >> type) {
        if (type == "ADD") {
            int x;
            cin >> x;
            if (!root) {
                root = new node(x);
                cout << "DONE\n";
            } else {
                root->add(x);
            }
        } else if (type == "SEARCH") {
            int x;
            cin >> x;
            if (root->search(x)) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        } else {
            root->print_tree();
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
