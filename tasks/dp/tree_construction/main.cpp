#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 3e5;
int n;
vector<int> g[MAXN];
int diam[MAXN];
int rad[MAXN];

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
    
}