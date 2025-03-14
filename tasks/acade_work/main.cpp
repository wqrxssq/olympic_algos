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

using ll = long long;
using ull = unsigned long long;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int, int>;
using pll = pair <ll, ll>;
using vpii = vector <pii>;
using vvi = vector <vi>;

const int INF = 1e9;
const ll INFLL = 1e18;
const int mod = 1e9 + 7;
const double eps = 1e-8;

struct SplayTree {
    int key;
    ll s;
    SplayTree *L = 0, *R = 0, *P = 0;

    SplayTree() {}
    SplayTree(int _key) : key(_key), s(_key) {}
};

ll get_s(SplayTree* v) {
    return (v ? v->s : 0);
}

void recalc_s(SplayTree* v) {
    v->s = get_s(v->L) + get_s(v->R) + v->key;
}

void set_parent(SplayTree* child, SplayTree* parent) {
    if (child) child->P = parent;
}
void update_parent(SplayTree* child, SplayTree* old_child) {
    SplayTree* parent = old_child->P;
    if (parent) {
        if (parent->L == old_child) {
            parent->L = child;
        } else {
            parent->R = child;
        }
    }
}

void zig(SplayTree* v) {
    SplayTree* p = v->P;
    if (p->L == v) {
        SplayTree* B = v->R;

        v->P = p->P;
        update_parent(v, p);

        v->R = p;

        p->P = v;
        p->L = B;

        set_parent(B, p);
    } else { // p->R == v
        SplayTree* B = v->L;

        v->P = p->P;
        update_parent(v, p);

        v->L = p;

        p->P = v;
        p->R = B;

        set_parent(B, p);
    }
    recalc_s(p);
    recalc_s(v);
}

void zig_zig(SplayTree* v) {
    zig(v->P);
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
SplayTree* find(SplayTree*& v, int key) {
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
    recalc_s(L);
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
        recalc_s(v);
        return {L, v};
    } else {
        SplayTree* R = v->R;
        set_parent(R, 0);
        v->R = 0;
        recalc_s(v);
        return {v, R};
    }
}

void insert(SplayTree*& v, int key) {
    find(v, key);
    if (v && v->key == key) {
        return;
    }
    SplayTree* temp = new SplayTree(key);
    auto [L, R] = split(v, key);
    v = merge(L, merge(temp, R));
}

ll sum(SplayTree*& v, int l, int r) {
    auto [M, R] = split(v, r + 1);
    auto [L, T] = split(M, l);
    ll ans = get_s(T);
    v = merge(L, merge(T, R));
    return ans;
}

void solve() {
    int n;
    cin >> n;
    SplayTree* root = 0;

    ll prev = 0;
    for (int i = 0; i < n; i++) {
        char type;
        cin >> type;
        if (type == '+') {
            int x;
            cin >> x;
            x = (x + prev) % INF;
            insert(root, x);
            prev = 0;
        } else {
            int l, r;
            cin >> l >> r;
            prev = sum(root, l, r);
            cout << prev << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
}
