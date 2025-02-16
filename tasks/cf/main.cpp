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

const int MAXN = 450000;
int n;
int a[MAXN];

struct node {
    int tl, tr;
    int sum = 0;
    node *l, *r;
    
    node(int tl_, int tr_) : tl(tl_), tr(tr_) {
        l = NULL;
        r = NULL;
    }

    void push() {
        if (l == NULL && tl != tr) {
            int tm = (tl + tr) >> 1;
            l = new node(tl, tm);
            r = new node(tm + 1, tr);
        }
    }

    void inc(int pos) {
        if (tl == tr) {
            sum++;
        } else {
            push();
            int tm = (tl + tr) >> 1;
            if (pos <= tm) {
                l->inc(pos);
            } else {
                r->inc(pos);
            }
            sum++;
        }
    }

    void upd(int pos, int x) {
        if (tl == tr) {
            sum += x;
        } else {
            int tm = (tl + tr) >> 1;
            if (pos <= tm) {
                l = new node(*l);
                l->upd(pos, x);
            } else {
                r = new node(*r);
                r->upd(pos, x);
            }
            sum = l->sum + r->sum;
        }
    }
};

node *root[MAXN + 1];

int get_kth(node *L, node *R, int k) {
    if (L->tl == L->tr) {
        return L->tl;
    } else {
        int cnt_left = L->l->sum - R->l->sum;
        if (cnt_left >= k)
            return get_kth(L->l, R->l, k);
        else
            return get_kth(L->r, R->r, k - cnt_left);
    }
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    root[0] = new node(0, INF);
    for (int i = 0; i < n; i++) {
        root[0]->inc(a[i]);
    }

    for (int i = 0; i < n; i++) {
        root[i + 1] = new node(*root[i]);
        root[i + 1]->upd(a[i], -1);
    }

    ll res = 0;
    int q;
    cin >> q;
    int prev_ans = 0;
    for (int i = 0; i < q; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        l = (l + prev_ans) % n + 1;
        r = (r + prev_ans) % n + 1;
        prev_ans = get_kth(root[l - 1], root[r], k);
        res += prev_ans;
    }
    cout << res << '\n';
}


int main() {
    fast_input;
#ifdef __APPLE__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    solve();
}