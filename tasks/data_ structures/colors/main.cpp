#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

struct query {
    int l, r, c;
};

const int MAXN = 8001;
int n;
int color[MAXN];
int ans[MAXN];

int p[MAXN];

void init() {
    fill(color, color + MAXN, -1);
    fill(ans, ans + MAXN, 0);
    iota(p, p + MAXN, 0);
}

int leader(int v) {
    return (v == p[v] ? v : p[v] = leader(p[v]));
}
void unite(int v, int u) {
    p[v] = u;
}

void solve() {
    init();
    vector<query> q(n);

    for (auto [l, r, c] : q) {
        int l, r, c;
        cin >> l >> r >> c;
    }

    reverse(q.begin(), q.end());
    
    for (auto [l, r, c] : q) {
        while (true) {
            l = leader(l);
            if (l >= r) {
                break;
            }
            color[l] = c;
            unite(l, l + 1);
        }
    }
    
    for (int l = 0, r = 0; l < MAXN; l = r) {
        while (r < MAXN && color[r] == color[l]) {
            r++;
        }
        if (color[l] >= 0) {
            ans[color[l]]++;
        }
    }
    
    for (int i = 0; i < MAXN; i++) {
        if (ans[i]) {
            cout << i << ' ' << ans[i] << '\n';
        }
    }
    cout << '\n';
}

int main() {
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    while (cin >> n) {
        solve();
    }
}