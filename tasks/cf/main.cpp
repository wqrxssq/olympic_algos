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
int k;
int red_buttons = 0;
int cur_iterations = 0;
int GREADY_OF_CELL[N];
int cur[N];
bool first_time = true;
int next_changes[N];
int is_gridy[N];

// Символ '0' соответствует городу, в котором сейчас нет ни Деда Мороза, ни запроса подарка.
// Символ '1' соответствует городу, в котором сейчас нет Деда Мороза, но есть запрос подарка.
// Символ '2' означает, что в этом городе сейчас есть активный запрос подарка, при этом в начале хода пришёл ещё один запрос подарка, но он не был активирован, так как ещё не истёк этот.
// Символ '3' означает, что в этом городе сейчас есть активный запрос подарка, при этом данный запрос появился только что, а запрос, который был в этой клетке один ход назад, исчез и превратился в нажатие красной кнопки.
// Символ 'd' - 4 означает, что в этом городе сейчас находится Дед Мороз и запроса подарка на этом ходу не поступало.
// Символ 'D' - 5 означает, что в этом городе сейчас находится Дед Мороз и запрос подарка поступал только что, но был сразу выполнен.

void scan(string& s) {
    for (int i = 0; i < N; i++) {
        char c = s[i];
        switch (c) {
        case '0':
            cur[i] = 0;
            break;
        case '1':
            cur[i] = 1;
            break;
        case '2':
            cur[i] = 2;
            GREADY_OF_CELL[i]++;
            break;
        case '3':
            cur[i] = 3;
            GREADY_OF_CELL[i] += 2;
            break;
        case 'd':
            cur[i] = 4;
            break;
        case 'D':
            cur[i] = 5;
            GREADY_OF_CELL[i]++;
            break;
        default:
            assert(false);
        }
    }
}

void first_pos() {
    int dist = N / k;
    int left = k;
    for (int i = 0; i < N; i++) {
        if (i % dist == 0 && left > 0) {
            left--;
            cur[i] = 1;
        }
    }

    for (int i = 0; i < N; i++) {
        cout << cur[i];
    }
    cout << endl;
}

void GET_GRIDY_CELLS_PRIOR() {
    vpii gred;
    for (int i = 0; i < N; i++) {
        gred.pb({GREADY_OF_CELL[i], i});
    }
    sort(rall(gred));

    for (int i = 0; i < k; i++) {
        is_gridy[gred[i].ss] = 1;
    }
}

void do_changes() {
    memset(next_changes, 0, sizeof(int) * N);

    if (red_buttons < 500) {
        for (int i = 0; i < N; i++) {
            switch (cur[i]) {
            case 4:
                next_changes[i] = 1;
            case 5:
                next_changes[i] = 1;
                break;
            default:
                break;
            }
        }
    } else {
        if (first_time) {
            GET_GRIDY_CELLS_PRIOR();
            first_time = 0;
        }

        int cnt_used_gridy = 0;
        for (int i = 0; i < N; i++) {
            if ((cur[i] == 4 || cur[i] == 5) && is_gridy[i]) {
                cnt_used_gridy++;
            } 
        }

        if (cnt_used_gridy == 0) {
            
        }
        for (int i = 0; i < N; i++) {
            switch (cur[i]) {
            case 4:
                next_changes[i] = 1;
            case 5:
                next_changes[i] = 1;
                break;
            default:
                break;
            }
        }
    }
}

void change_cur() {
    for (int i = 0; i < N; i++) {
        switch (next_changes[i]) {
        case 1:
            cout << 'R';
            break;
        case -1:
            cout << 'L';
            break;
        case 0:
            cout << 'N';
            break;
        case 2:
            cout << 'S';
            break;
        default:
            break;
        }
    }
    cout << endl;
}

void solve() {
    cin >> k;
    first_pos();
    while (red_buttons < 10000) {
        cur_iterations++;
        cin >> red_buttons;
        if (red_buttons >= 10000) break;
        string s;
        cin >> s;
        scan(s);
        do_changes();
        change_cur();
    }
}

int main() {
    fast_input;
    solve();
}
