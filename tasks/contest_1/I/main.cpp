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

const int MAXN = 101;
const int MAXW = 1001;
int n, S;
int w[MAXN], c[MAXN], ph[MAXN];
int dp[MAXN * MAXW];

int sdp[MAXN][MAXN * MAXW];
int p[MAXN][MAXN * MAXW];

void solve() {
    cin >> n >> S;
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> c[i] >> ph[i];
    }

    int max_cost = -1;
    int best_ph = -1;
    for (int i = 0; i < n; i++) {
        int pressure = ph[i];
        vpii v;
        int sum_w = 0;
        int sum_cost = 0;
        for (int j = 0; j < n; j++) {
            if (ph[j] >= pressure) {
                sum_w += w[j];
                sum_cost += c[j];
                v.pb({w[j], c[j]});
            }
        }

        if (sum_w <= S + pressure) {
            if (sum_cost > max_cost) {
                max_cost = sum_cost;
                best_ph = pressure;
            }
            continue;
        }

        int capacity = S + pressure + 1;

        fill(dp, dp + capacity, -INF);
        dp[0] = 0;

        for (int j = 0; j < sz(v); j++) {
            for (int W = min(capacity - 1, MAXW * (j + 1)); W >= v[j].ff; W--) {
                dp[W] = max(dp[W], dp[W - v[j].ff] + v[j].ss);
            }
        }

        sum_cost = *max_element(dp, dp + capacity);
        if (sum_cost > max_cost) {
            max_cost = sum_cost;
            best_ph = pressure;
        }
    }
    // cout << max_cost << ' ' << best_ph << '\n';

    vpii v;
    vi id;
    int sum_w = 0;
    for (int i = 0; i < n; i++) {
        if (ph[i] >= best_ph) {
            sum_w += w[i];
            v.pb({w[i], c[i]});
            id.pb(i);
        }
    }

    int capacity = min(S + best_ph + 1, sum_w + 1);
    fill(*sdp, *sdp + (MAXN * MAXN * MAXW), -INF);
    sdp[0][0] = 0;
    p[0][0] = -1;

    for (int i = 0; i < sz(v); i++) {
        for (int j = 0; j < capacity; j++) {
            sdp[i + 1][j] = sdp[i][j];
            p[i + 1][j] = p[i][j];
        }

        for (int j = v[i].ff; j < capacity; j++) {
            if (sdp[i][j - v[i].ff] + v[i].ss > sdp[i + 1][j]) {
                sdp[i + 1][j] = sdp[i][j - v[i].ff] + v[i].ss;
                p[i + 1][j] = i;
            }
        }
    }

    int best_w = 0;
    max_cost = 0;
    for (int i = 0; i < capacity; i++) {
        if (max_cost < sdp[sz(v)][i]) {
            max_cost = sdp[sz(v)][i];
            best_w = i;
        }
    }
    int pos = p[sz(v)][best_w];
    vi ans;
    while (pos != -1) {
        ans.pb(id[pos]);
        best_w = best_w - v[pos].ff;
        pos = p[pos][best_w];
    }

    cout << sz(ans) << ' ' << max_cost << '\n';
    for (int x : ans) {
        cout << x + 1 << ' ';
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