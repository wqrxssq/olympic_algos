#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

typedef long long ll;
const ll INFLL = 1e18;
struct seg {
    int l, r, c;
};

// 2 1 1 1 2 2 2

// 3 1 2 1 3 2 1 2 4 3

void solve() {
    int n;
    cin >> n;
    vector<seg> a(n);
    for (auto &[l, r, c] : a) {
        int t;
        cin >> l >> t >> c;
        r = l + t;
    }

    sort(a.begin(), a.end(), [](seg &a, seg &b) {
        return a.r < b.r;
    });
    vector<pair<int, ll>> ans;
    ans.push_back({0, 0});
    for (auto &[l, r, c] : a) {
        pair<int, ll> s = {l, INFLL};
        auto [r_best, c_best] = ans[upper_bound(ans.begin(), ans.end(), s) - ans.begin() - 1];
        c_best += c;
        if (ans.back().second < c_best) {
            ans.push_back({r, c_best});
        }
    }

    cout << ans.back().second << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}