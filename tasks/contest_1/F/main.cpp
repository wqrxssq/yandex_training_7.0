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
#define fast_input ios_base::sync_with_stdio(0)
#define setpr cout << setprecision(6) << fixed

const int MAXW = 10001;
const int MAXN = 101;
int n, W;
int w[MAXN], c[MAXN];
int dp[MAXN][MAXW];
int pr[MAXN][MAXW];

void solve() {
    cin >> n >> W;
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    fill(*dp, *dp + (MAXN * MAXW), -INF);
    dp[0][0] = 0;
    pr[0][0] = -1;

    for (int i = 0; i < n; i++) {
        copy(*dp + (i * MAXW), *dp + ((i + 1) * MAXW), *dp + ((i + 1) * MAXW));
        copy(*pr + (i * MAXW), *pr + ((i + 1) * MAXW), *pr + ((i + 1) * MAXW));
        for (int j = w[i]; j <= W; j++) {
            if (dp[i][j - w[i]] + c[i] > dp[i + 1][j]) {
                dp[i + 1][j] = dp[i][j - w[i]] + c[i];
                pr[i + 1][j] = i;
            }
        }
    }

    int max_cost = -1;
    int best_w = 0;
    for (int i = 0; i <= W; i++) {
        if (dp[n][i] > max_cost) {
            max_cost = dp[n][i];
            best_w = i;
        }
    }

    int pos = pr[n][best_w];
    while (pos != -1) {
        cout << pos + 1 << '\n';
        best_w = best_w - w[pos];
        pos = pr[pos][best_w];
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