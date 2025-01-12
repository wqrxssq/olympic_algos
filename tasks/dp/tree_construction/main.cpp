#include <iostream>
#include <vector>
#include <set>
using namespace std;

const int INF = 1e9;

const int MAXN = 3e5;
int n;
vector<int> g[MAXN];
int diam[MAXN];
int rad[MAXN];

int ans = INF;

void dfs(int v, int p = -1) {
    int max_r1 = -1, max_r2 = -1;

    for (int u : g[v]) {
        if (u == p) {
            continue;
        }
        dfs(u, v);
        diam[v] = max(diam[u], diam[v]);
        if (rad[u] > max_r1) {
            max_r2 = max_r1;
            max_r1 = rad[u];
        } else if (rad[u] > max_r2) {
            max_r2 = rad[u];
        }
    }
    rad[v] = max_r1 + 1;
    diam[v] = max(diam[v], max_r1 + max_r2 + 2);
}

void calc(int v, int p = -1) {
    set<pair<int, int>> rads;
    set<pair<int, int>> diams;
    for (int u : g[v]) {
        rads.insert({rad[u], u});
        diams.insert({diam[u], u});
    }

    for (int u : g[v]) {
        if (u == p) {
            continue;
        }
        // delete edge v, u
        rads.erase({rad[u], u});
        diams.erase({diam[u], u});

        // find_diam1(v), find_diam2(u)
        int rad1_v = (rads.size() == 0 ? -1 : (--rads.end())->first);
        int rad2_v = (rads.size() < 2 ? -1 : (--(--rads.end()))->first);
        int diam_v = (diams.size() == 0 ? 0 : (--diams.end())->first);
        int diam1 = max(rad1_v + rad2_v + 2, diam_v);

        int diam2 = diam[u];
        ans = min(ans, max(diam1, max(diam2, 1 + (diam1 + 1) / 2 + (diam2 + 1) / 2)));

        // insert edge v, u
        rads.insert({rad[u], u});
        diams.insert({diam[u], u});
    }
}

int main() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int v, u;
        cin >> v >> u;
        v--; u--;
        g[v].push_back(u);
        g[u].push_back(v);
    }

    dfs(0);

    calc(0);
}