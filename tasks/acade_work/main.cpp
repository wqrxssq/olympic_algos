#pragma GCC optimize("O3,unroll-loops")
#include <functional>
#include <iostream>
#include <bitset>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <queue>
#include <math.h>
#include <vector>
#include <string>
#include <stack>
#include <cassert>
#include <random>
#include <chrono>
#include <cstring>
#include <iomanip>
using namespace std;
const int MAX_BLOCKS = 1000;
struct Rect {
    int top, left, bottom, right;
    bitset<MAX_BLOCKS> coverage;
};

string bin(int x, int len) {
    string s;
    for (int i = 0; i < len; ++i) {
        s += '0'+x%2;
        x /= 2;
    }
    reverse(s.begin(), s.end());
    return s;
}

bool can(int n, int m, int k, vector<vector<int>> pref, vector<string> grid) {
    auto rectSum = [&](int top, int left, int bottom, int right) -> int {
        return pref[bottom+1][right+1] - pref[top][right+1] - pref[bottom+1][left] + pref[top][left];
    };
    vector<int> candTop, candBottom, candLeft, candRight;
    for (int i = 0; i < n; i++){
        bool isTop = false, isBottom = false;
        for (int j = 0; j < m; j++){
            if (grid[i][j]=='1'){
                if(i == 0 || grid[i-1][j]=='0')
                    isTop = true;
                if(i == n-1 || grid[i+1][j]=='0')
                    isBottom = true;
            }
        }
        if(isTop) candTop.push_back(i);
        if(isBottom) candBottom.push_back(i);
    }
    for (int j = 0; j < m; j++){
        bool isLeft = false, isRight = false;
        for (int i = 0; i < n; i++){
            if (grid[i][j]=='1'){
                if(j == 0 || grid[i][j-1]=='0')
                    isLeft = true;
                if(j == m-1 || grid[i][j+1]=='0')
                    isRight = true;
            }
        }
        if(isLeft) candLeft.push_back(j);
        if(isRight) candRight.push_back(j);
    }

    sort(candTop.begin(), candTop.end());
    candTop.erase(unique(candTop.begin(), candTop.end()), candTop.end());
    sort(candBottom.begin(), candBottom.end());
    candBottom.erase(unique(candBottom.begin(), candBottom.end()), candBottom.end());
    sort(candLeft.begin(), candLeft.end());
    candLeft.erase(unique(candLeft.begin(), candLeft.end()), candLeft.end());
    sort(candRight.begin(), candRight.end());
    candRight.erase(unique(candRight.begin(), candRight.end()), candRight.end());
    vector<Rect> candidates;

    for (int top : candTop){
        for (int bottom : candBottom){
            if (top > bottom) continue;
            for (int left : candLeft){
                for (int right : candRight){
                    if (left > right) continue;
                    int area = (bottom - top + 1) * (right - left + 1);
                    if (rectSum(top, left, bottom, right) == area) {
                        Rect r;
                        r.top = top; r.left = left; r.bottom = bottom; r.right = right;
                        candidates.push_back(r);
                    }
                }
            }
        }
    }
    vector<int> compRows, compCols;
    compRows.push_back(0); compRows.push_back(n);
    for (int x : candTop) {
        compRows.push_back(x);
        if(x+1 <= n) compRows.push_back(x+1);
    }
    for (int x : candBottom) {
        compRows.push_back(x);
        if(x+1 <= n) compRows.push_back(x+1);
    }
    sort(compRows.begin(), compRows.end());
    compRows.erase(unique(compRows.begin(), compRows.end()), compRows.end());
    compCols.push_back(0); compCols.push_back(m);
    for (int x : candLeft) {
        compCols.push_back(x);
        if(x+1 <= m) compCols.push_back(x+1);
    }
    for (int x : candRight) {
        compCols.push_back(x);
        if(x+1 <= m) compCols.push_back(x+1);
    }
    sort(compCols.begin(), compCols.end());
    compCols.erase(unique(compCols.begin(), compCols.end()), compCols.end());
    int Rblocks = compRows.size() - 1;
    int Cblocks = compCols.size() - 1;
    int totalBlocks = Rblocks * Cblocks;
    bitset<MAX_BLOCKS> target;
    target.reset();
    for (int i = 0; i < Rblocks; i++){
        for (int j = 0; j < Cblocks; j++){
            int r1 = compRows[i], r2 = compRows[i+1]-1;
            int c1 = compCols[j], c2 = compCols[j+1]-1;
            char val = grid[r1][c1];
            int idx = i * Cblocks + j;
            if (val == '1')
                target.set(idx, true);
        }
    }
    for (auto &rect : candidates) {
        bitset<MAX_BLOCKS> cov;
        cov.reset();
        for (int i = 0; i < Rblocks; i++){
            int rowStart = compRows[i], rowEnd = compRows[i+1]-1;
            if (rect.top <= rowStart && rect.bottom >= rowEnd){
                for (int j = 0; j < Cblocks; j++){
                    int colStart = compCols[j], colEnd = compCols[j+1]-1;
                    if (rect.left <= colStart && rect.right >= colEnd){
                        int idx = i * Cblocks + j;
                        cov.set(idx, true);
                    }
                }
            }
        }
        rect.coverage = cov;
    }
    int candCount = candidates.size();
    vector<bitset<MAX_BLOCKS>> unionSuffix(candCount+1);
    unionSuffix[candCount].reset();
    for (int i = candCount - 1; i >= 0; i--) {
        unionSuffix[i] = unionSuffix[i+1] | candidates[i].coverage;
    }
    vector<int> solIndices;
    vector<int> bestSolution;
    bool found = false;
    function<void(int,int, bitset<MAX_BLOCKS>)> dfs = [&](int idx, int count, bitset<MAX_BLOCKS> cur) {
        if (found) return;
        if (count == k) {
            if (cur == target) {
                bestSolution = solIndices;
                found = true;
            }
            return;
        }
        if (idx >= candCount) return;
        if ((cur | unionSuffix[idx]) != target) return;
        if (count + (candCount - idx) < k) return;
        for (int i = idx; i < candCount; i++) {
            solIndices.push_back(i);
            dfs(i+1, count+1, cur | candidates[i].coverage);
            solIndices.pop_back();
            if (found) return;
        }
    };
    bitset<MAX_BLOCKS> empty; empty.reset();
    dfs(0, 0, empty);
    if (!found) {
        return false;
    }

    cout << bin(n, 10) << bin(m, 10) << bin(k, 4); 

    for (int idx : bestSolution) {
        Rect r = candidates[idx];

        cout << bin(r.top, 10) << bin(r.left, 10) << bin(r.bottom, 10) << bin(r.right, 10);

        // cout << (r.top + 1) << " " << (r.left + 1) << " " 
        //      << (r.bottom + 1) << " " << (r.right + 1) << "\n";
    }
    return true;
}

void encode() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<string> grid(n);
    for (int i = 0; i < n; i++){
        cin >> grid[i];
    }
    vector<vector<int>> pref(n+1, vector<int>(m+1, 0));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            pref[i+1][j+1] = (grid[i][j]=='1') + pref[i][j+1] + pref[i+1][j] - pref[i][j];
        }
    }

    for (int i = 1; i <= k; i++) {
        if (can(n, m, i, pref, grid)) {
            break;
        }
    }
}

int get_int_from_bits(int len) {
    int val = 0;
    char c;
    for (int i = 0; i < len; i++) {
        cin >> c;
        val *= 2;
        val += (c - '0');
    }
    return val;
}

void decode() {
    int n = get_int_from_bits(10), m = get_int_from_bits(10);
    int k = get_int_from_bits(4);

    vector<vector<int>> grid(n, vector<int>(m));

    for (int i = 0; i < k; i++) {
        int l = get_int_from_bits(10), x = get_int_from_bits(10), r = get_int_from_bits(10), y = get_int_from_bits(10);
        for (int j = l; j <= r; j++) {
            for (int s = x; s <= y; s++) {
                grid[j][s] = 1;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << grid[i][j];
        }
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    string s;
    cin >> s;
    if (s == "encode") {
        encode();
    } else {
        decode();
    }
}
