#include <math.h>

#include <algorithm>
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
using namespace std;

using ll = long long;
using ull = unsigned long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vll = vector<ll>;
using pii = pair<int, int>;
using vpii = vector<pii>;

const double eps = 0.0001;
const int INF = 1e9;
const ll INFLL = 1e18;
const int MOD = 1e9 + 7;

#define all(_x) _x.begin(), _x.end()
#define rall(_x) _x.rbegin(), _x.rend()
#define pb push_back
#define ff first
#define ss second
#define sz(_x) (int)_x.size()
#define display(_x)                       \
    for (auto el : _x) cout << el << ' '; \
    cout << '\n'
#define cin_arr(_x) \
    for (auto &el : _x) cin >> el;
#define fast_input ios_base::sync_with_stdio(0)
#define setpr cout << setprecision(6) << fixed

// ok
struct SplayTree {
    int size;
    int L, R, P;
    bool rev;

    SplayTree() : size(1), L(-1), R(-1), P(-1), rev(false) {}
};

// ok
const int MAXN = 1e5 + 100;
int n;
SplayTree t[MAXN];

// ok
int get_size(int v) {
    return (v == -1 ? 0 : t[v].size);
}

// ok
void update(int v) {
    if(v == -1) return;
    t[v].size = get_size(t[v].L) + get_size(t[v].R) + 1;
}

// ok
void push(int v) {
    if (t[v].rev) {
        if (t[v].L != -1)
            t[t[v].L].rev ^= 1;
        if (t[v].R != -1)
            t[t[v].R].rev ^= 1;
        swap(t[v].R, t[v].L);
        t[v].rev = 0;
    }
}

// ok
bool is_root(int v) {
    int p = t[v].P;
    return p == -1 || (t[p].L != v && t[p].R != v);
}

// ok
void set_parent(int child, int parent) {
    if(child != -1) {
        t[child].P = parent;
    }
}

// ok
void update_parent(int child, int old_child) {
    int parent = t[old_child].P;
    if(parent != -1) {
        if(t[parent].L == old_child)
            t[parent].L = child;
        else if (t[parent].R == old_child)
            t[parent].R = child;
    }
}

// ok
void zig(int v) {
    int p = t[v].P;
    if(p == -1) return;
    push(p);
    push(v);
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

// ok
void zig_zig(int v) {
    zig(t[v].P);
    zig(v);
}

// ok
void zig_zag(int v) {
    zig(v);
    zig(v);
}

// ok
void splay(int v) {
    while(!is_root(v)) {
        int p = t[v].P;
        if(is_root(p))
            zig(v);
        else {
            int g = t[p].P;
            if((t[g].L == p && t[p].L == v) || (t[g].R == p && t[p].R == v))
                zig_zig(v);
            else
                zig_zag(v);
        }
    }
    push(v);
}

// ok
int expose(int x) {
    int c = -1;
	for (int y = x; y != -1; y = t[y].P) {
		splay(y);
		t[y].R = c;
		update(y);
		c = y;
	}
	splay(x);
    return c;
}

// ok
void reroot(int v) {
    expose(v);
    t[v].rev ^= 1;
}

// ok
void link(int v, int u) {
    reroot(v);
    t[v].P = u;
}

// ok
void cut_parent(int v) {
    expose(v);
    set_parent(t[v].L,  -1);
	t[v].L = -1;
    // update(v);
}

// ok
void cut(int v, int u) {
    reroot(v);
    cut_parent(u);
}

// ok
bool path(int v, int u) {
    if (v == u)
        return true;
    expose(u);
    expose(v);
    return t[u].P != -1;
}

// ok
int lca(int v, int u) {
    if (!path(v, u)) {
        return -1;
    }
    expose(v);
    return expose(u);
}

// ok
int depth(int v) {
    expose(v);
    return get_size(t[v].L);
}

// ok
int distance(int v, int u) {
    int x = lca(v, u);
    if (x == -1)
        return -1;
    return depth(u) + depth(v) - depth(x) * 2;
}

void solve() {
    int m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        string type;
        int v, u;
        cin >> type >> v >> u;
        v--; u--;
        if (type == "get") {
            cout << distance(v, u) << '\n';
        } else if (type == "link") {
            link(v, u);
        } else {
            cut(v, u);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}