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

const int MAXN = 5000;
const int MAXK = 100;
const int MAX_CNT_COLOR = 50;
const int MAXS = MAX_CNT_COLOR * MAXK + 1;

int n, k;
int L[MAXN], s[MAXK];
vpii w[MAXK];

int p[MAXK][MAXS];
int dp[MAXK][MAXS];

void solve() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int color;
        cin >> L[i] >> color;
        color--;
        w[color].pb({L[i], i});
        s[color] += L[i];
    }

    int S = s[0];
    for (int i = 0; i < k; i++) {
        if (S != s[i]) {
            cout << "NO\n";
            return;
        }
    }

    for (int i = 0; i < k; i++) {
        dp[i][0] = 1;
        for (auto [x, id] : w[i]) {
            for (int j = S; j >= x; j--) {
                if (!dp[i][j] && dp[i][j - x]) {
                    dp[i][j] = 1;
                    p[i][j] = id;
                }
            }
        }
    }

    int best_a = 0;
    for (int a = 1; a < S; a++) {
        bool flag = true;
        for (int i = 0; i < k; i++) {
            flag &= dp[i][a];
        }
        if (flag) {
            best_a = a;
            break;
        }
    }

    if (best_a) {
        cout << "YES\n";
        for (int i = 0; i < k; i++) {
            int temp_a = best_a;
            while (temp_a) {
                cout << p[i][temp_a] + 1 << ' ';
                temp_a -= L[p[i][temp_a]];
            }
        }
        cout << '\n';
    } else {
        cout << "NO\n";
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