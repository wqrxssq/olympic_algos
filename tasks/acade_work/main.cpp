#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b) {
    return (a.second < b.second) || (a.second == b.second && a.first > b.first);
}

void solve() {
    int n;
    cin >> n;
    int k = 1;
    vector<pair<int, int>> seg;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        seg.push_back({l, r});
    }

    sort(seg.begin(), seg.end(), cmp);

    int ans = 0;
    queue<int> q;
    for (auto [l, r] : seg) {
        while (q.size() > 0 && q.front() <= l) {
            q.pop();
        }
        if (q.size() < k) {
            ans++;
            q.push(r);
        }
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}