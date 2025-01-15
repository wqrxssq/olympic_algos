#include <iostream>
#include <queue>
using namespace std;

void solve() {
    int n;
    cin >> n;
    queue<pair<string, int>> q;
    q.push({"1", 1 % n});
    while (true) {
        auto [s, m] = q.front();
        if (m == 0) {
            cout << s << '\n';
            break;
        }
        q.pop();
        q.push({s + "0", (m * 10) % n});
        q.push({s + "1", (m * 10 + 1) % n});
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}