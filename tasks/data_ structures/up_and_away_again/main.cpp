#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include <cassert>
using namespace std;

const int MAXN = 1e5;
int n;
int h[MAXN];
int d[MAXN];
int r[MAXN];
int dist[MAXN];

void bfs(int start) {
    set<pair<int, int>> ls;
    for (int i = 0; i < n; i++) {
        ls.insert({h[i], i});
    }

    fill(dist, dist + n, -1);
    dist[start] = 0;
    queue<int> q;
    q.push(start);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        while (!ls.empty() && ls.lower_bound({h[v], 0}) != ls.end() && ls.lower_bound({h[v], 0})->first <= r[v]) {
            auto [height, u] = *ls.lower_bound({h[v], 0});
            if (dist[u] == -1) {
                dist[u] = dist[v] + 1;
                q.push(u);
            }
            ls.erase({height, u});
        }
    }
}

void solve() {
    int x, t;
    cin >> n >> x >> t;
    x--;

    for (int i = 0; i < n; i++) {
        cin >> h[i];
        h[i]--;
    }
    for (int i = 0; i < n; i++) {
        cin >> d[i];
        r[i] = h[i] + d[i];
    }

    bfs(x);

    if (dist[0] == -1) {
        cout << -1 << '\n';
    } else {
        cout << 1LL * dist[0] * t << '\n';
    }
}

int main() {
    solve();
}