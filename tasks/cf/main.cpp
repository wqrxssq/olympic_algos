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
// #define sz(_x) (int)_x.size()
#define ff first
#define ss second
#define pb push_back
#define display(_x) for (int x : a) cout << x << ' '; cout << '\n';
#define fast_input ios_base::sync_with_stdio(0); cin.tie(0);
#define cin_arr(_x) for (int &x : a) cin >> x;

mt19937 rnd((int)chrono::steady_clock::now().time_since_epoch().count());

const int INF = 1e9;
const int MOD = 1e9 + 7;
const double EPS = 1e-6;

struct Node {
    int priority;

    int value, sum, lazy;

    char c;
    int sz;

    Node* l = nullptr;
    Node* r = nullptr;

    Node (int _value) : priority(rnd()), value(_value), sum(_value), lazy(1), sz(1) {
    }
};

const int POWER = 31;
const int MAXN = 1e6;
int n;
int del[MAXN];

string s;
int p[MAXN], rev_p[MAXN];
int h[MAXN];

Node* t;
int len = 0;

int add(int a,int b) {
    return a + b >= MOD ? a + b - MOD : a + b;
}

int mult(int a,int b) {
    return 1LL * a * b % MOD;
}

int getSz(Node* t) {
    if (t == nullptr) {
        return 0;
    }
    return t->sz;
}

int getSum(Node* t) {
    if (t == nullptr) {
        return 0;
    }
    return t->sum;
}

int bpow(int a, int n, int mod) {
    int res = 1;
    while (n) {
        if (n & 1) { 
            res = 1LL * res * a % mod;
        }
        n >>= 1;
        a = 1LL * a * a % mod;
    }
    return res;
}

void push(Node *t) {
    if (t == nullptr) {
        return;
    }
    if(t->lazy == 1) {
        return;
    }

    if (t->l != nullptr) {
        t->l->lazy = mult(t->l->lazy, t->lazy);
        t->l->sum = mult(t->l->sum, t->lazy);
        t->l->value = mult(t->l->value, t->lazy);
    }

    if (t->r != nullptr) {
        t->r->lazy = mult(t->r->lazy, t->lazy);
        t->r->sum = mult(t->r->sum, t->lazy);
        t->r->value = mult(t->r->value, t->lazy);
    }

    t->lazy = 1;
}

void update(Node *t) {
    t->sz = getSz(t->l) + getSz(t->r) + 1;
    t->sum = add(add(getSum(t->l), getSum(t->r)), t->value);
}

pair<Node*, Node*> split(Node *t, int x) {
    if (t == nullptr) {
        return {nullptr, nullptr};
    }
    push(t);

    int sz = getSz(t->l) + 1;
    if (x >= sz) {
        auto [l, r] = split(t->r, x - sz);
        t->r = l;
        update(t);
        return {t, r};
    } else {
        auto [l, r] = split(t->l, x);
        t->l = r;
        update(t);
        return {l, t};
    }
}

Node* merge(Node* l, Node* r) {
    if (l == nullptr) {
        return r;
    }
    if (r == nullptr) {
        return l;
    }

    push(l);
    push(r);

    if (l->priority > r->priority) {
        l->r = merge(l->r, r);
        update(l);
        return l;
    } else {
        r->l = merge(l, r->l);
        update(r);
        return r;
    }
}

Node* erase(int x) {
    auto [l, r] = split(t, x);
    auto [l1, r1] = split(r, 1);

    if (r1 != nullptr) {
        r1->lazy = mult(r1->lazy, rev_p[1]);
        r1->sum = mult(r1->sum, rev_p[1]);
        r1->value = mult(r1->value, rev_p[1]);
    }
    return merge(l, r1);
}

Node* insert(int x, int val){
    auto [l, r] = split(t, x);
    Node* newNode = new Node(val);

    if(r != nullptr){
        r->lazy = mult(r->lazy, p[1]);
        r->sum = mult(r->sum, p[1]);
        r->value = mult(r->value, POWER);
    }

    return merge(merge(l, newNode), r);
}

bool preiod(int x) {
    auto [l, r] = split(t, len - x);
    int s1 = l->sum;

    t = merge(l, r);

    auto [l1, r1] = split(t, x);
    int s2 = r1->sum;
    t = merge(l1, r1);

    return s1 == mult(s2, rev_p[x]);
}

void init() {
    p[0] = 1;
    rev_p[0] = 1;

    for (int i = 1; i < MAXN; i++) {
        p[i] = mult(p[i - 1], POWER);
        rev_p[i] = bpow(p[i], MOD-2, MOD);
    }

    for (int i = 2; i < MAXN; i++){
        if (!del[i]) {
            for (int j = i; j < MAXN; j += i) {
                if (!del[j]) {
                    del[j] = i;
                }
            }
        }
    }
}

void solve() {
    init();
    cin >> n >> s;

    t = nullptr;
    for (int i = 0; i < n; i++) {
        h[i] = mult((s[i] - 'a' + 1), p[i+1]);
        Node* newNode = new Node(h[i]);
        t = merge(t, newNode);
    }

    len = n;
    del[1] = 1;

    int q;
    cin >> q;
    while (q--) {
        char tp;
        int x;
        cin >> tp;
        if (tp == '?') {
            if (len == 1) {
                cout << 1 << '\n';
            } else if (preiod(1)) {
                cout << 1 << '\n';
            } else if (del[len] == len) {
                cout << len << '\n';
            } else {
                int x = len;
                int x1 = len;
                while (x1 != 1) {
                    if (preiod(x / del[x1])) {
                        x /= del[x1];
                    }
                    x1 /= del[x1];
                }
                cout << x << '\n';
            }
        } else if (tp == '-') {
            cin >> x;
            --len;
            t = erase(x);
        } else {
            char c;
            cin >> x >> c;
            len++;
            t = insert(x, mult((c - 'a' + 1), p[x + 1]));
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