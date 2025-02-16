#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <deque>
#include <queue>
#include <string>
#include <stack>
#include <cassert>
#include <iomanip>
#include <random>
#include <chrono>
#include <cstring>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using vi = vector <int>;
using vvi = vector <vi>;
using vll = vector <ll>;
using pii = pair <int, int>;
using vpii = vector <pii>;

#define all(_x) _x.begin(), _x.end()
#define rall(_x) _x.rbegin(), _x.rend()
#define sz(_x) (int)_x.size()
#define ff first
#define ss second
#define pb push_back
#define display(_x) for (int x : a) cout << x << ' '; cout << '\n';
#define fast_input ios_base::sync_with_stdio(0); cin.tie(0);
#define cin_arr(_x) for (int &x : a) cin >> x;

const int INF = 1e9;
const ll INFLL = 1e18;
const int MOD = 1e9 + 7;

struct query{
    int x, y;
    int id;
};
struct dot{
    int l, r;
    int y;
    int type;
};

struct Node {
    int tl, tr;
    Node *l = 0, *r = 0;
    int add = 0;

    Node (int tl_, int tr_) : tl(tl_), tr(tr_) {}

    void push() {
        if (!l && tl != tr) {
            int tm = (tl + tr) >> 1;
            l = new Node(tl, tm);
            l->add = add;
            r = new Node(tm + 1, tr);
            r->add = add;
            add = 0;
        }
    }
    
    void add_x(int ql, int qr, int x) {
        if (ql > qr) {
            return;
        }
        if (tl == ql && tr == qr) {
            add += x;
        } else {
            push();
            int tm = (tl + tr) >> 1;
            l->add_x(ql, min(tm, qr), x);
            r->add_x(max(tm + 1, ql), qr, x);
        }
    }

    int get(int pos) {
        if (tl == tr) {
            return add;
        }
        push();
        int tm = (tl + tr) >> 1;
        if (pos <= tm) {
            return add + l->get(pos);
        } else {
            return add + r->get(pos);
        }
    }
};

const int MAXN = 2e5;
int n;
int lx[MAXN], rx[MAXN];
int ly[MAXN], ry[MAXN];
vector<dot> d;

// кол-во отрезков которым принадлежит x
int get_cnt_x(int x) {
    return n - ((lower_bound(rx, rx + n, x) - rx) + n - (upper_bound(lx, lx + n, x) - lx));
}

// кол-во отрезков которым принадлежит y
int get_cnt_y(int y) {
    return n - ((lower_bound(ry, ry + n, y) - ry) + n - (upper_bound(ly, ly + n, y) - ly));
}

void solve() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> lx[i] >> rx[i];
        cin >> ly[i] >> ry[i];
        d.pb({lx[i], rx[i], ly[i], 1});
        d.pb({lx[i], rx[i], ry[i], -1});
    }

    sort(lx, lx + n); sort(rx, rx + n);
    sort(ly, ly + n); sort(ry, ry + n);

    sort(all(d), [](dot a, dot b) {
        return a.y < b.y || (a.y == b.y && a.type > b.type);
    });

    int res = 0;
    int p = -1, q = -1;

    Node *root = new Node(0, INF);

    int prev_y = -1;
    vpii need_to_calc;
    for (auto [l, r, y, type] : d) {
        if (y != prev_y) {
            for (auto [x, t] : need_to_calc) {
                int cur = get_cnt_x(x) + get_cnt_y(t) - root->get(x);
                // int xxx = get_cnt_x(x);
                // int xxy = get_cnt_y(t);
                // int xxz = root->get(x);
                if (cur > res) {
                    res = cur;
                    p = x;
                    q = t;
                }
            }
            need_to_calc.clear();
        }
        root->add_x(l, r, type);
        need_to_calc.pb({l, y});
        need_to_calc.pb({r, y});
        prev_y = y;
    }

    for (auto [x, y] : need_to_calc) {
        int cur = get_cnt_x(x) + get_cnt_y(y) - root->get(x);
        if (cur > res) {
            res = cur;
            p = x;
            q = y;
        }
    }

    cout << p << ' ' << q << '\n';
}

int main() {
    fast_input;
#ifdef __APPLE__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    solve();
}