#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;

const int INF = 1e9;
const int MAXN = 100000;

struct SplayTree {
    int size;
    int val, min_el;
    bool is_rev;
    int L, R, P;
    
    SplayTree() {}
    SplayTree(int _val) : size(1), val(_val), min_el(_val), is_rev(false), L(-1), R(-1), P(-1) {}
};

SplayTree t[MAXN];
int nodes_count = 0;

int new_node(int val) {
    t[nodes_count] = SplayTree(val);
    return nodes_count++;
}

int get_size(int v) {
    return (v == -1 ? 0 : t[v].size);
}

int get_min_val(int v) {
    return (v == -1 ? INF : t[v].min_el);
}

void update(int v) {
    if(v == -1) return;
    t[v].size = get_size(t[v].L) + get_size(t[v].R) + 1;
    t[v].min_el = min({ get_min_val(t[v].L), get_min_val(t[v].R), t[v].val });
}

void push(int v) {
    if(v == -1) return;
    if (t[v].is_rev) {
        if (t[v].L != -1) t[t[v].L].is_rev ^= 1;
        if (t[v].R != -1) t[t[v].R].is_rev ^= 1;
        swap(t[v].L, t[v].R);
        t[v].is_rev = false;
    }
}

void set_parent(int child, int parent) {
    if(child != -1)
        t[child].P = parent;
}

void update_parent(int child, int old_child) {
    int parent = t[old_child].P;
    if(parent != -1) {
        if(t[parent].L == old_child)
            t[parent].L = child;
        else
            t[parent].R = child;
    }
}

void zig(int v) {
    int p = t[v].P;
    if(p == -1) return;
    if(t[p].L == v) {
        int B = t[v].R;
        t[v].P = t[p].P;
        update_parent(v, p);
        t[v].R = p;
        t[p].P = v;
        t[p].L = B;
        set_parent(B, p);
    } else {
        int B = t[v].L;
        t[v].P = t[p].P;
        update_parent(v, p);
        t[v].L = p;
        t[p].P = v;
        t[p].R = B;
        set_parent(B, p);
    }
    update(p);
    update(v);
}

void zig_zig(int v) {
    zig(t[v].P);
    zig(v);
}

void zig_zag(int v) {
    zig(v);
    zig(v);
}

void splay(int v) {
    while(t[v].P != -1) {
        int p = t[v].P;
        if(t[p].P == -1)
            zig(v);
        else {
            int g = t[p].P;
            if((t[g].L == p && t[p].L == v) || (t[g].R == p && t[p].R == v))
                zig_zig(v);
            else
                zig_zag(v);
        }
    }
}

int get_kth(int v, int k) {
    push(v);
    int left_size = get_size(t[v].L);
    if(left_size + 1 == k) {
        if(t[v].L != -1) push(t[v].L);
        splay(v);
        return v;
    } else if(k <= left_size)
        return get_kth(t[v].L, k);
    else
        return get_kth(t[v].R, k - left_size - 1);
}

int merge(int L, int R) {
    if(L == -1) return R;
    if(R == -1) return L;
    push(L);
    while(t[L].R != -1) {
        push(L);
        L = t[L].R;
        push(L);
    }
    splay(L);
    t[L].R = R;
    t[R].P = L;
    update(L);
    return L;
}

pair<int, int> split(int v, int x) {
    if(v == -1) return {-1, -1};
    if(x <= 0) return {-1, v};
    if(x >= get_size(v)) return {v, -1};
    v = get_kth(v, x);
    int R = t[v].R;
    set_parent(R, -1);
    t[v].R = -1;
    update(v);
    return {v, R};
}

void push_back(int &v, int val) {
    int temp = new_node(val);
    v = merge(v, temp);
}

void reverse_interval(int &v, int l, int r) {
    auto AB = split(v, l);
    int A = AB.first, B = AB.second;
    auto CD = split(B, r - l + 1);
    int C = CD.first, D = CD.second;
    if(C != -1) t[C].is_rev ^= 1;
    v = merge(merge(A, C), D);
}

int query_min(int &v, int l, int r) {
    auto AB = split(v, l);
    int A = AB.first, B = AB.second;
    auto CD = split(B, r - l + 1);
    int C = CD.first, D = CD.second;
    int res = get_min_val(C);
    v = merge(merge(A, C), D);
    return res;
}

void solve() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    int root = -1;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        push_back(root, x);
    }
    while(m--) {
        int type, l, r;
        cin >> type >> l >> r;
        l--; r--;
        if(type == 1)
            reverse_interval(root, l, r);
        else
            cout << query_min(root, l, r) << "\n";
    }
}

int main(){
    solve();
    return 0;
}
