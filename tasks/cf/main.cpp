#pragma GCC optimize("O3,unroll-loops")

#include <math.h>

#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <climits>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vll = vector<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vpii = vector<pii>;
const double PI = acos(-1);
const double EPS = 1e-6;
const int INF = 1e9;
const ll INFLL = 1e18;
const int MOD = 1e9 + 7;

mt19937 rnd(static_cast<unsigned int>(chrono::steady_clock().now().time_since_epoch().count()));

#define all(_x) _x.begin(), _x.end()
#define rall(_x) _x.rbegin(), _x.rend()
#define pb push_back
#define ff first
#define ss second
#define sz(_x) (int)_x.size()
#define display(_x)        \
    for (auto el : _x)     \
        cout << el << ' '; \
    cout << '\n'
#define cin_arr(_x)     \
    for (auto& el : _x) \
        cin >> el;
#define fast_input ios_base::sync_with_stdio(0); cin.tie(0)
#define setpr(_x) cout << setprecision(_x) << fixed
#define debug(x) cout << __FUNCTION__ << ": " << #x " = " << (x) << endl

const int N = 100;
int red_buttons = 0;

tuple<vector<int>, vector<int>, map<int, int>> decode_input(string &s, int k) {
    vector<int> positions_of_santas;
    vector<int> positions_of_box;
    map<int, int> count_of_boxes_in_square;

    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '0') continue;
        if (s[i] == '1') {
            positions_of_box.push_back(i);
            count_of_boxes_in_square[i]++;
        } else if (s[i] == '2') {
            positions_of_box.push_back(i);
            count_of_boxes_in_square[i]++;
        } else if (s[i] == '3'){
            red_buttons++;
            positions_of_box.push_back(i);
            count_of_boxes_in_square[i]++;
        } else if (s[i] == 'd') {
            positions_of_santas.push_back(i);
        } else if (s[i] == 'D') {
            positions_of_santas.push_back(i);
            count_of_boxes_in_square[i]++;
        }
    }

    return make_tuple(positions_of_santas, positions_of_box, count_of_boxes_in_square);
}

void ask(vector<pair<int, int>> ded) {
    string result(N, 'N');
    for (int i = 0; i < ded.size(); i++) {
        if (ded[i].second == 0) {
            result[ded[i].first] = 'S';
        } else if (ded[i].second == 1) {
            result[ded[i].first] = 'R';
        } else if (ded[i].second == -1) {
            result[ded[i].first] = 'L';
        } else {
            assert(false);
        }
    }
    cout << result << endl;
}

void send_pos(vi &pos) {
    for (int x : pos) {
        cout << x;
    }
    cout << endl;
}

void first_pos(int k) {
    vector<int> perm(100);
    int dist = 100 / k;
    int left = k;
    for (int i = 0; i < 100; i++) {
        if (i % dist == 0 && left > 0) {
            left--;
            perm[i] = 1;
        }
    }
    send_pos(perm);
}

vector<pair<int, int>> fun(tuple<vector<int>, vector<int>, map<int, int>> input) {
    auto positions_of_santas = get<0>(input);
    auto positions_of_box = get<1>(input);
    auto count_of_boxes_in_square = get<2>(input);

    vector<pair<int, int>> ans;
    if (red_buttons == 0) {
        for (int x : positions_of_santas) {
            ans.push_back({x, 0});
        }
    } else {
        for (int x : positions_of_santas) {
            ans.push_back({x, 1});
        }
    }
    return ans;
}


void solve() {
    int k;
    cin >> k;
    first_pos(k);
    while (red_buttons < 10000) {
        cin >> red_buttons;
        if (red_buttons >= 10000) break;
        string s;
        cin >> s;
        ask(fun(decode_input(s, k)));
    }
}

int main() {
    fast_input;
    solve();
}
