#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 90;
const int MOD = 2009;

vector<vector<int>> mul(vector<vector<int>> a, vector<vector<int>> b) {
    int n = (int)a.size();
    vector<vector<int>> c(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                c[i][j] += a[i][k] * b[k][j];
                c[i][j] %= MOD;
            }
        }
    }
    return c;
}

vector<vector<int>> binpow(vector<vector<int>> d, int n) {
    if (n == 1) {
        return d;
    }
    vector<vector<int>> tmp = binpow(d, n / 2);
    tmp = mul(tmp, tmp);
    return (n % 2 ? mul(tmp, d) : tmp);
}

void solve() {
    int n, t;
    cin >> n >> t;
    vector<vector<int>> g(MAXN, vector<int>(MAXN));
    for (int i = 0; i < n; i++) {
        string gi;
        cin >> gi;
        for (int j = 0; j < n; j++) {
            int k = gi[j] - '0';
            if (k == 0) {
                continue;
            } else if (k == 1) {
                g[i][j] = 1;
            } else {
                int s = n + i * 8;
                g[i][s] = 1;
                for (int z = 1; z < k - 1; z++) {
                    g[s][s + 1] = 1;
                    s++;
                }
                g[s][j] = 1;
            }
        }
    }
    
    vector<vector<int>> d = binpow(g, t);
    cout << d[0][n - 1] << '\n';
}

int main() {
    solve();
}