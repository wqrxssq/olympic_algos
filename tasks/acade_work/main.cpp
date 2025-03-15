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

class LinkCutTree {
   private:
    struct Vertex {
        int left, right, parent;
        bool revert;
        int size;

        Vertex()
            : left(-1),
              right(-1),
              parent(-1),
              revert(),
              size(1) {}
    };

    vector<Vertex> t;

    bool isRoot(int x) const {
        int p = t[x].parent;
        return p == -1 || (t[p].left != x && t[p].right != x);
    }

    void push(int x) {
        if (t[x].revert) {
            if (t[x].left != -1) t[t[x].left].revert = !t[t[x].left].revert;
            if (t[x].right != -1) t[t[x].right].revert = !t[t[x].right].revert;
            swap(t[x].left, t[x].right);
            t[x].revert = false;
        }
    }

    void keep(int x) {
        t[x].size = 1;
        if (t[x].left != -1) {
            t[x].size += t[t[x].left].size;
        }
        if (t[x].right != -1) {
            t[x].size += t[t[x].right].size;
        }
    }

    void rotate(int x) {
        int p = t[x].parent;
        int g = t[p].parent;
        push(p), push(x);
        if (g != -1) {
            if (t[g].left == p)
                t[g].left = x;
            else if (t[g].right == p)
                t[g].right = x;
        }
        t[x].parent = g;
        if (t[p].left == x) {
            t[p].left = t[x].right;
            if (t[p].left != -1) t[t[p].left].parent = p;
            t[x].right = p;
        } else {
            t[p].right = t[x].left;
            if (t[p].right != -1) t[t[p].right].parent = p;
            t[x].left = p;
        }
        t[p].parent = x;
        keep(p), keep(x);
    }

    void splay(int x) {
        while (!isRoot(x)) {
            int p = t[x].parent;
            if (!isRoot(p)) {
                int g = t[p].parent;
                bool zigzig = (x == t[p].left) == (p == t[g].left);
                rotate(zigzig ? p : x);
            }
            rotate(x);
        }
        push(x);
    }

    int expose(int x) {
        int c = -1;
        for (int y = x; y != -1; y = t[y].parent) {
            splay(y);
            t[y].right = c;
            keep(y);
            c = y;
        }
        splay(x);
        return c;
    }

   public:
    LinkCutTree(int n) : t(n) {}

    void evert(int x) {
        expose(x);
        t[x].revert = !t[x].revert;
    }

    bool path(int x, int y) {
        if (x == y) return true;
        expose(y), expose(x);
        return t[y].parent != -1;
    }

    void link(int x, int y) {
        if (path(x, y)) return;
        evert(x);
        t[x].parent = y;
    }

    void cut(int x) {
        expose(x);
        if (t[x].left == -1) return;
        t[t[x].left].parent = -1;
        t[x].left = -1;
    }

    void cut_edge(int v, int u) {
        evert(v);
        cut(u);
    }

    int lca(int x, int y) {
        if (!path(x, y)) return -1;
        expose(x);
        return expose(y);
    }

    int depth(int x) {
        expose(x);
        if (t[x].left == -1) return 0;
        return t[t[x].left].size;
    }

    int distance(int x, int y) {
        int l = lca(x, y);
        if (l == -1) return -1;
        return depth(y) + depth(x) - depth(l) * 2;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    LinkCutTree q(n);
    for (int i = 0; i < m; i++) {
        string type;
        int v, u;
        cin >> type >> v >> u;
        v--;
        u--;
        if (type == "get") {
            cout << q.distance(v, u) << '\n';
        } else if (type == "link") {
            q.link(v, u);
        } else {
            q.cut_edge(v, u);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
