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

const int MAXN = 1000;
pii a[MAXN], b[MAXN];
int ans[MAXN];
int n, m;

void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i].ff;
        a[i].ss = i;
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i].ff;
        b[i].ff--;
        b[i].ss = i;
    }

    sort(a, a + n);
    sort(b, b + m);
    memset(ans, -1, sizeof(ans));

    int res = 0;
    for (int l = 0, r = 0; l < n && r < m; l++) {
        while (r < m && a[l].ff > b[r].ff) {
            r++;
        }
        if (r < m && a[l].ff <= b[r].ff) {
            ans[a[l].ss] = b[r].ss;
            r++;
            res++;
        }
    }
    cout << res << '\n';
    for (int i = 0; i < n; i++) {
        cout << ans[i] + 1 << ' ';
    }
    cout << '\n';
}

int main() {
    fast_input;
#ifdef __APPLE__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    solve();
}