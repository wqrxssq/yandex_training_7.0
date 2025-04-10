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

const int MAXN = 31;
ll a[MAXN];

bool check(ll x, int m) {
    ll res = 0;
    for (int i = MAXN - 1; i >= 0; i--) {
        if (x >= (1 << i)) {
            res += a[i];
            x -= 1LL * (1 << i);
        }
    }
    return res >= m;
}

void solve() {
    int m;
    cin >> m;
    for (int i = 0; i < MAXN; i++) {
        cin >> a[i];
        a[i] = max(a[i], (i == 0 ? 0 : a[i - 1] * 2));
    }

    ll l = 0, r = 1e9;
    // f(r) = 1
    // f(l) = 0
    while (r - l > 1) {
        ll x = (l + r) >> 1;
        if (check(x, m)) {
            r = x;
        } else {
            l = x;
        }
    }
    cout << r << '\n';
}

int main() {
    fast_input;
#ifdef __APPLE__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    solve();
}