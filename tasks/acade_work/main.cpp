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
    int size;
    SplayTree *L = 0, *R = 0, *P = 0;

    SplayTree() {}
    SplayTree(int _key) : key(_key), size(1) {}
};

ll get_size(SplayTree* v) {
    return (v ? v->size : 0);
}

void update(SplayTree* v) {
    v->size = get_size(v->L) + get_size(v->R) + 1;
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
    update(p);
    update(v);
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
    update(L);
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
        update(v);
        return {L, v};
    } else {
        SplayTree* R = v->R;
        set_parent(R, 0);
        v->R = 0;
        update(v);
        return {v, R};
    }
}

void insert(SplayTree*& v, int key) {
    find(v, key);
    SplayTree* temp = new SplayTree(key);
    auto [L, R] = split(v, key);
    v = merge(L, merge(temp, R));
}

/*
erase node with key = x, or do nothing, if where is no key = x
*/
void erase(SplayTree*& v, int x) {
    v = find(v, x);
    if (v && v->key == x) {
        SplayTree* L = v->L;
        SplayTree* R = v->R;
        set_parent(L, 0);
        set_parent(R, 0);
        delete v;
        v = merge(L, R);
    }
}

int get_kth(SplayTree*& v, int k) {
    while (true) {
        if (k == get_size(v->R) + 1) {
            splay(v);
            return v->key;
        }
        if (get_size(v->R) >= k) {
            v = v->R;
        } else {
            k -= get_size(v->R) + 1;
            v = v->L;
        }
    }
}

void solve() {
    int n;
    cin >> n;
    SplayTree* root = 0;
    for (int i = 0; i < n; i++) {
        string s;
        int x;
        cin >> s >> x;
        if (s == "0") {
            cout << get_kth(root, x) << '\n';
        } else if (s == "-1") {
            erase(root, x);
        } else {
            insert(root, x);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
}
