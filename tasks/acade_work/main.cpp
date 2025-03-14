#pragma GCC optimize("O3,unroll-loops")

#include <iostream>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <queue>
#include <math.h>
#include <vector>
#include <string>
#include <stack>
#include <cassert>
#include <random>
#include <chrono>
#include <cstring>
#include <iomanip>
using namespace std;

#define all(_x) _x.begin(), _x.end()
#define rall(_x) _x.rbegin(), _x.rend()
#define pb push_back
#define sz(_x) (int)_x.size()
#define ff first
#define ss second
#define cin_arr(a)for (int _ii = 0; _ii < (int)a.size(); _ii++)  \
    cin >> a[_ii];
#define display(a) for (auto _ii : a)                            \
    cout << _ii << ' ';                                          \
cout << '\n';
#define display_pairs(a) for (auto _ii : a)                      \
    cout << _ii.ff << ' ' << _ii.ss << '\n';
#define display_matrix(a) for (auto _row : a)                    \
{                                                                \
    for (auto _cell : _row)                                      \
        cout << _cell << ' ';                                    \
    cout << '\n';                                                \
}                                                                \
cout << '\n'
#define fast_input ios_base::sync_with_stdio(0); cin.tie(0)
#define fast_interactive_input ios_base::sync_with_stdio(0)

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> pii;
typedef pair <ll, ll> pll;
typedef vector <pii> vpii;
typedef vector <vi> vvi;

const int INF = 1e9;
const ll INFLL = 1e18;
const int mod = 1e9 + 7;
const double eps = 1e-6;

struct SplayTree {
    int key, val;
    SplayTree *L = 0, *R = 0, *P = 0;

    SplayTree() {}
    SplayTree(int _key, int _val) : key(_key), val(_val) {}
};

void set_parent(SplayTree* child, SplayTree* parent) {
    if (child) child->P = parent;
}

void zig(SplayTree* v) {
    SplayTree* p = v->P;
    if (p->L == v) {
        SplayTree* B = v->R;

        v->P = p->P;
        if (p->P) {
            if (p->P->L == p)
                p->P->L = v;
            else if (p->P->R == p)
                p->P->R = v;
        }

        v->R = p;

        p->P = v;
        p->L = B;

        set_parent(B, p);
    } else { // p->R == v
        SplayTree* B = v->L;

        v->P = p->P;
        if (p->P) {
            if (p->P->L == p)
                p->P->L = v;
            else if (p->P->R == p)
                p->P->R = v;
        }

        v->L = p;

        p->P = v;
        p->R = B;

        set_parent(B, p);
    }
}

void zig_zig(SplayTree* v) {
    SplayTree* p = v->P;
    zig(p);
    zig(v);
}

void zig_zag(SplayTree* v) {
    zig(v);
    zig(v);
}

void splay(SplayTree* v) {
    while (v->P) {
        SplayTree* p = v->P;
        if (!p->P) {
            zig(v);
        } else {
            SplayTree* g = p->P;
            bool zigzig = (g->L == p && p->L == v) || (g->R == p && p->R == v);
            if (zigzig) {
                zig_zig(v);
            } else {
                zig_zag(v);
            }
        }
    }
}

/*
find key and return node with this key, and this node becomes root.
P.S. if where is no such key, find will return first bigger or first lower node, but never 0
*/
SplayTree* find(SplayTree* v, int key) {
    if (!v) {
        return 0;
    }
    // as normal BST, but use splay before return
    while (true) {
        if (v->key == key) {
            splay(v);
            return v;
        }
        if (key < v->key) {
            if (!v->L) {
                splay(v);
                return v;
            }
            v = v->L;
        } else {
            if (!v->R) {
                splay(v);
                return v;
            }
            v = v->R;
        }
    }
}

/*
merge 2 nodes,
all keys in L < all keys in R
*/
SplayTree* merge(SplayTree* L, SplayTree* R) {
    if (!L) return R;
    if (!R) return L;

    while (L->R) {
        L = L->R;
    }
    splay(L);
    L->R = R;
    R->P = L;
    return L;
}

/*
return 2 nodes [L, R], 
where all keys in L < x, and all keys in R >= x
*/
pair<SplayTree*, SplayTree*> split(SplayTree* v, int x) {
    if (!v) return {0, 0};
    v = find(v, x);

    if (v->key >= x) {
        SplayTree* L = v->L;
        set_parent(L, 0);
        v->L = 0;
        return {L, v};
    } else {
        SplayTree* R = v->R;
        set_parent(R, 0);
        v->R = 0;
        return {v, R};
    }
}

/*
returns first node, which key >= x
*/
SplayTree* lower_bound(SplayTree* v, int x) {
    auto [L, R] = split(v, x);
    SplayTree* temp = R;
    while (temp && temp->L) temp = temp->L;
    splay(temp);
    v = merge(L, R);
    return temp;
}

SplayTree* insert(SplayTree* v, int key, int val) {
    SplayTree* temp = new SplayTree(key, val);
    auto [L, R] = split(v, key);
    return merge(L, merge(temp, R));
}

/*
erase node with key = x, or do nothing, if where is no key = x
*/
SplayTree* erase(SplayTree* v, int x) {
    v = find(v, x);
    if (v && v->key == x) {
        SplayTree* L = v->L;
        SplayTree* R = v->R;
        set_parent(L, 0);
        set_parent(R, 0);
        delete v;
        return merge(L, R);
    }
    return v;
}

void solve() {
    int n;
    cin >> n;
    SplayTree* root = 0;
    for (int i = 0; i < n; i++) {
        int x = 2 * i, val = i;
        root = insert(root, x, val);
    }

    for (int i = 0; i < 2 * n; i++) {
        SplayTree* v = find(root, i);
        assert(v == root);

        if (i % 2 == 0) {
            assert(v != 0);
            assert(v->key == i);
        } else {
            assert(v == 0 || v->key != i);
        }

        root = erase(root, i);
        assert(find(root, i) == 0 || find(root, i)->key != i);
    }
}

int main() {
    fast_input;
    solve();
}
