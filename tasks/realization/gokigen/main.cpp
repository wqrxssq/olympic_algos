#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MAXN = 10;
int n;
int ans[MAXN][MAXN];
int puzzle[MAXN][MAXN];
bool is_succes = false;

int used[MAXN][MAXN];
vector<pair<int, int>> g[MAXN][MAXN];

bool check_cycle(int i, int j, int prev_i = -1, int prev_j = -1) {
    bool res = 0;
    used[i][j] = 1;
    for (auto [v, u] : g[i][j]) {
        if (v == prev_i && u == prev_j) {
            continue;
        }
        if (used[v][u]) {
            return true;
        }
        res |= check_cycle(v, u, i, j);
    }
    return res;
}

bool check(int i, int j, int k) {
    if ((int)g[i][j].size() != puzzle[i][j] && puzzle[i][j] != -1) {
        return false;
    }
    if (j == n - 1) {
        if ((int)g[i][j + 1].size() != puzzle[i][j + 1] && puzzle[i][j + 1] != -1) {
            return false;
        }
    }
    if (i == n - 1) {
        if ((int)g[i + 1][j].size() != puzzle[i + 1][j] && puzzle[i + 1][j] != -1) {
            return false;
        }
    }
    if (i == n - 1 && j == n - 1) {
        if ((int)g[i + 1][j + 1].size() != puzzle[i + 1][j + 1] && puzzle[i + 1][j + 1] != -1) {
            return false;
        }
    }

    if ((int)g[i + 1][j + 1].size() > puzzle[i + 1][j + 1] && puzzle[i + 1][j + 1] != -1) {
        return false;
    }
    if ((int)g[i][j + 1].size() > puzzle[i][j + 1] && puzzle[i][j + 1] != -1) {
        return false;
    }
    if ((int)g[i + 1][j].size() > puzzle[i + 1][j] && puzzle[i + 1][j] != -1) {
        return false;
    }

    memset(used, 0, sizeof(int) * MAXN * MAXN);
    if (k == 0) {
        return !check_cycle(i, j);
    } else {
        return !check_cycle(i + 1, j);
    }
}

void calc(int i, int j) {
    if (i == n) {
        is_succes = true;
    }
    
    for (int k = 0; k < 2; k++) {
        ans[i][j] = k;
        if (k == 0) {
            g[i][j].push_back({i + 1, j + 1});
            g[i + 1][j + 1].push_back({i, j});
        } else {
            g[i][j + 1].push_back({i + 1, j});
            g[i + 1][j].push_back({i, j + 1});
        }
        
        if (check(i, j, k)) {
            if (j == n - 1) {
                calc(i + 1, 0);
            } else {
                calc(i, j + 1);
            }
            if (is_succes) {
                return;
            }
        }
        
        if (k == 0) {
            g[i][j].pop_back();
            g[i + 1][j + 1].pop_back();
        } else {
            g[i][j + 1].pop_back();
            g[i + 1][j].pop_back();
        }
    }
}


void solve() {
    cin >> n;
    for (int i = 0; i <= n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j <= n; j++) {
            if (s[j] == '.') {
                puzzle[i][j] = -1;
            } else {
                puzzle[i][j] = (s[j] - '0');
            }
        }
    }
    
    calc(0, 0);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << (ans[i][j] == 0 ? '\\' : '/');
        }
        cout << '\n';
    }
}

int main() {
    solve();
}