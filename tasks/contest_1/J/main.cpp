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

struct event {
    string s;
    int W;
};

const int MAXN = 1000;
const int MAXW = 10001;
int n, D;
event a[MAXN];
int dp[MAXW];

void solve() {
    cin >> n >> D;
    for (int i = 0; i < n; i++) {
        cin >> a[i].s >> a[i].W;
    }

    sort(a, a + n, [&](event& a, event& b) {
        return a.W < b.W;
    });

    fill(dp, dp + MAXW, INF);
    dp[0] = 0;

    vector<string> ans;
    int K = 0, S = 0, T = 0;
    for (; K < n; K++) {
        if (a[K].W - S > D) {
            break;
        }

        ans.pb(a[K].s);
        S += a[K].W;
        int l = max(0, a[K].W - D);
        int r = a[K].W + 1;
        int cost = *min_element(dp + l, dp + r) + 1;
        T += cost;

        for (int j = MAXW - 1; j >= a[K].W; j--) {
            dp[j] = min(dp[j], dp[j - a[K].W] + cost);
        }
    }

    sort(all(ans));
    cout << K << ' ' << T << '\n';
    for (string& s : ans) {
        cout << s << '\n';
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