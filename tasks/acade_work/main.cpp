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
    int size;
    int val, min_el;
    bool is_rev = false;
    SplayTree *L = 0, *R = 0, *P = 0;

    SplayTree() {}
    SplayTree(int _val) : size(1), val(_val), min_el(_val) {}
};

int get_size(SplayTree* v) {
    return (v ? v->size : 0);
}
int get_min(SplayTree* v) {
    return (v ? v->min_el : INF);
}

void update(SplayTree* v) {
    v->size = get_size(v->L) + get_size(v->R) + 1;
    v->min_el = min(min(get_min(v->L), get_min(v->R)), v->val);
}

void push(SplayTree* v) {
    if (v->is_rev) {
        if (v->L) v->L->is_rev = true;
        if (v->R) v->R->is_rev = true;
        swap(v->L, v->R);
        v->is_rev = false;
    }
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

SplayTree* get_kth(SplayTree*& v, int k) {
    if (!v) {
        return 0;
    }
    // as normal BST, but use splay before return
    while (true) {
        push(v);
        if (get_size(v->L) + 1 == k) {
            if (v->L) {
                push(v->L);
            }
            splay(v);
            return v;
        }
        if (k <= get_size(v->L)) {
            v = v->L;
        } else {
            k -= get_size(v->L) + 1;
            v = v->R;
        }
    }
}

SplayTree* merge(SplayTree* L, SplayTree* R) {
    if (!L) return R;
    if (!R) return L;

    while (L->R) {
        push(L);
        L = L->R;
    }
    push(L);
    splay(L);
    L->R = R;
    R->P = L;
    update(L);
    return L;
}

// return [L, R], where sz(L) == k, so it means we get first k elements
pair<SplayTree*, SplayTree*> split(SplayTree* v, int x) {
    if (!v) return {0, 0};
    if (x <= 0) return {nullptr, v};
    if (x >= get_size(v)) return {v, nullptr};
    // v is k_th
    // so it has k - 1 in left
    v = get_kth(v, x);
    SplayTree* R = v->R;
    set_parent(R, 0);
    v->R = 0;
    update(v);
    return {v, R};
}

void push_back(SplayTree*& v, int val) {
    SplayTree* temp = new SplayTree(val);
    v = merge(v, temp);
}

void reverse(SplayTree*& v, int l, int r) {
    auto [M, R] = split(v, r + 1);
    auto [L, T] = split(M, l);
    T->is_rev = true;
    v = merge(merge(L, T), R);
}

int get_min(SplayTree*& v, int l, int r) {
    auto [M, R] = split(v, r + 1);
    auto [L, T] = split(M, l);
    int res = get_min(T);
    v = merge(merge(L, T), R);
    return res;
}

void solve() {
    int n, m;
    cin >> n >> m;

    SplayTree* root = 0;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        push_back(root, x);
    }
    for (int i = 0; i < m; i++) {
        int type, l, r;
        cin >> type >> l >> r;
        l--;
        r--;
        if (type == 1)
            reverse(root, l, r);
        else
            cout << get_min(root, l, r) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
}
