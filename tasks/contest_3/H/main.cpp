#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <deque>
#include <queue>
#include <string>
#include <stack>
#include <cassert>
#include <iomanip>
#include <random>
#include <chrono>
#include <cstring>
#include <bitset>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using vi = vector <int>;
using vvi = vector <vi>;
using vll = vector <ll>;
using pii = pair <int, int>;
using pll = pair <ll, ll>;
using vpii = vector <pii>;
const double eps = 0.0001;
const int INF = 1e9;
const ll INFLL = 1e18;
const int MOD = 1e9 + 7;

#define all(_x) _x.begin(), _x.end()
#define rall(_x) _x.rbegin(), _x.rend()
#define pb push_back
#define ff first
#define ss second
#define sz(_x) (int)_x.size()
#define display(_x) for (auto el : _x) cout << el << ' '; cout << '\n'
#define cin_arr(_x) for (auto &el : _x) cin >> el;
#define fast_input ios_base::sync_with_stdio(0); cin.tie(0)
#define setpr cout << setprecision(6) << fixed

const int MAXN = 128;
int n;
ll t[MAXN][MAXN][MAXN];

void inc(int x, int y, int z, int m) {
    for (int i = x; i < n; i |= i + 1)
        for (int j = y; j < n; j |= j + 1)
            for (int k = z; k < n; k |= k + 1)
                t[i][j][k] += m;
}
ll sum(int x, int y, int z) {
    ll res = 0;
    for (int i = x; i > -1; i = (i & (i + 1)) - 1)
        for (int j = y; j > -1; j = (j & (j + 1)) - 1)
            for (int k = z; k > -1; k = (k & (k + 1)) - 1)
                res += t[i][j][k];
    return res;
}
ll sum(int i1, int i2, int j1, int j2, int z1, int z2) {
    return sum(i2, j2, z2) - sum(i1 - 1, j2, z2) - sum(i2, j1 - 1, z2) + sum(i1 - 1, j1 - 1, z2)
    - sum(i2, j2, z1 - 1) + sum(i1 - 1, j2, z1 - 1) + sum(i2, j1 - 1, z1 - 1) - sum(i1 - 1, j1 - 1, z1 - 1);
}

void solve() {
    cin >> n;
    while (true) {
        int type;
        cin >> type;
        if (type == 1) {
            int i, j, z, x;
            cin >> i >> j >> z >> x;
            inc(i, j, z, x);
        } else if (type == 2) {
            int i1, j1, z1, i2, j2, z2;
            cin >> i1 >> j1 >> z1 >> i2 >> j2 >> z2;
            cout << sum(i1, i2, j1, j2, z1, z2) << '\n';
        }
        if (type == 3)
            break;
    }
}

int main() {
    fast_input;
#ifdef __APPLE__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    solve();
}