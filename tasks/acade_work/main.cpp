#include <iostream>
#include <unordered_set>
using namespace std;

const int MAXN = 500;
int ans[MAXN];
int cur_cnt = 0;

bool is_happy(int n) {
    unordered_set<int> q;
    while (!q.count(n)) {
        q.insert(n);
        int s = 0;
        while (n) {
            s += (n % 10) * (n % 10);
            n /= 10;
        }
        if (s == 1) {
            return true;
        }
        n = s;
    }
    return false;
}

void precalc() {
    for (int i = 1; cur_cnt < MAXN; i++) {
        if (is_happy(i)) {
            ans[cur_cnt++] = i;
        }
    }
}

void solve() {
    int n;
    cin >> n;
    cout << ans[n - 1] << '\n';
}

int main() {
    precalc();
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}