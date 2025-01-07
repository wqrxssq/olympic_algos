#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

const int INF = 1e9;

const int MAXN = 20;
int n;
string sp[MAXN];

// значение баланса для каждой строки
int last[MAXN];

// значение баланса скобок для каждой маски
int balance[1 << MAXN];

// состояние - {маска, флаг был ли хоть один отрицательный префикс}
int dp[1 << MAXN][2];

unordered_map<int, vector<int>> q[MAXN];

int get_balance(int id) {
    int balance = 0;
    for (int i = 0; i < (int)sp[id].size(); i++) {
        balance += (sp[id][i] == '(' ? 1 : -1);
        q[id][balance].push_back(i);
    }
    return balance;
}

int f(int balance, int id) {
    // проверим, что при добавлении к маске id, не появится отрицательного префикса
    if (q[id].count(-balance - 1)) {
        return -INF;
    } else {
        // найдем кол-во префиксов которые при присоединении новой строки даст 0
        return (q[id].count(-balance) ? q[id][-balance].size() : 0);
    }
}

int g(int balance, int id) {
    // проверим, что при добавлении к маске id, появится отриц. префикс
    if (!q[id].count(-balance - 1)) {
        return -INF;
    } else {
        // найдем кол-во префиксов которые при присоединении новой строки даст 0, но идут до позиции с отриц. префиксом
        int i = q[id][-balance - 1][0];
        return (q[id].count(-balance) ? lower_bound(q[id][-balance].begin(), q[id][-balance].end(), i) - q[id][-balance].begin() : 0);
    }
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> sp[i];
        last[i] = get_balance(i);
    }
    
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                balance[mask] += last[i];
            }
        }
    }

    for (int mask = 1; mask < (1 << n); mask++) {
        for (int from = 0; from < n; from++) {
            if (mask & (1 << from)) {
                dp[mask][0] = max(dp[mask][0], dp[mask ^ (1 << from)][0]
                    + f(balance[mask ^ (1 << from)], from));

                dp[mask][1] = max(dp[mask][1], dp[mask ^ (1 << from)][1]);
                dp[mask][1] = max(dp[mask][1], dp[mask ^ (1 << from)][0] 
                    + g(balance[mask ^ (1 << from)], from));
            }
        }
    }
    
    cout << max(dp[(1 << n) - 1][0], dp[(1 << n) - 1][1]) << '\n';
}

int main() {
    solve();
}