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

void solve() {
    int n;
    cin >> n;
    vi a(n);
    cin_arr(a);

    vi ans;
    int cur_min = INF;
    int cur_len = 0;
    for (int x : a) {
        cur_min = min(cur_min, x);
        if (cur_min < cur_len + 1) {
            ans.pb(cur_len);
            cur_len = 0;
        }
        cur_len++;
        if (cur_min == cur_len) {
            ans.pb(cur_len);
            cur_len = 0;
            cur_min = INF;
        }
    }
    if (cur_len)
        ans.pb(cur_len);
    cout << sz(ans) << '\n';
    display(ans);
}

int main() {
    fast_input;
#ifdef __APPLE__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}