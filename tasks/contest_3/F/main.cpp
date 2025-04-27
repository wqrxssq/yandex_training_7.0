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

const int MAXN = 1e3;
int n;
bitset<MAXN> has_xy[MAXN], has_xz[MAXN], has_yz[MAXN];

void solve() {
    int k;
    cin >> n >> k;
    for (int i = 0; i < k; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        x--; y--; z--;

        has_xy[x][y] = 1;
        has_yz[y][z] = 1;
        has_xz[x][z] = 1;
    }

    bitset<MAXN> mask;
    for (int i = 0; i < n; i++) {
        mask[i] = 1;
    }

    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            if (!has_xy[x][y]) {
                bitset<MAXN> inter = (mask & ~has_yz[y]) & (mask & ~has_xz[x]);

                if (inter.any()) {
                    int z = -1;
                    for (int i = 0; i < n; i++) {
                        if (!has_yz[y][i] && !has_xz[x][i]) {
                            z = i;
                        }
                    }

                    cout << "NO\n";
                    cout << x + 1 << ' ' << y + 1 << ' ' << z + 1 << '\n';
                    return;
                }
            }
        }
    }

    cout << "YES\n";
}

int main() {
    fast_input;
#ifdef __APPLE__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    solve();
}