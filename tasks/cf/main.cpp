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

struct Node {
    int tl, tr;
    int sum;
    int cnt_uniq;
    int cnt_diff;

    Node *L = 0, *R = 0;
    Node(int tl_, int tr_) : tl(tl_), tr(tr_), sum(0), cnt_uniq(0), cnt_diff(0) {
        if (tl == tr) {
            return;
        }
        int tm = (tl + tr) >> 1;
        L = new Node(tl, tm);
        R = new Node(tm + 1, tr);
    }

    void copy() {
        L = new Node(*L);
        R = new Node(*R);
    }

    void add(int pos, int x) {
        if (tl == tr) {
            sum = max(sum + x, 0);
            if (sum) {
                cnt_diff = 1;
            } else {
                cnt_diff = 0;
            }
            if (sum == 1) {
                cnt_uniq = 1;
            } else {
                cnt_uniq = 0;
            }
        } else {
            copy();
            int tm = (tl + tr) >> 1;
            if (pos <= tm) {
                L->add(pos, x);
            } else {
                R->add(pos, x);
            }
            sum = L->sum + R->sum;
            cnt_uniq = L->cnt_uniq + R->cnt_uniq;
            cnt_diff = L->cnt_diff + R->cnt_diff;
        }
    }

    int get_count(int pos) {
        if (tl == tr) {
            return sum;
        }
        int tm = (tl + tr) >> 1;
        if (pos <= tm) {
            return L->get_count(pos);
        } else {
            return R->get_count(pos);
        }
    }
};

const int MAXN = 4e5;
int n, m;
Node *version[MAXN];

void solve() {
    cin >> n >> m;
    version[0] = new Node(1, MAXN);

    int sum = 0;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        if (s == "add") {
            int x;
            cin >> x;
            version[i + 1] = new Node(*version[i]);
            version[i + 1]->add(x, 1);
        } else if (s == "remove") {
            int x;
            cin >> x;
            version[i + 1] = new Node(*version[i]);
            version[i + 1]->add(x, -1);
        } else if (s == "different") {
            int y;
            cin >> y;
            int v = (y + sum) % (i + 1);
            int res = version[v]->cnt_diff;
            cout << res << '\n';
            sum += res;
            version[i + 1] = new Node(*version[v]);
        } else if (s == "unique") {
            int y;
            cin >> y;
            int v = (y + sum) % (i + 1);
            int res = version[v]->cnt_uniq;
            cout << res << '\n';
            sum += res;
            version[i + 1] = new Node(*version[v]);
        } else {
            int x, y;
            cin >> x >> y;
            int v = (y + sum) % (i + 1);
            int res = version[v]->get_count(x);
            cout << res << '\n';
            sum += res;
            version[i + 1] = new Node(*version[v]);
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