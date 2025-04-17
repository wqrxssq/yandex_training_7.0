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

const int MAXN = 2e5;
int a[MAXN];
int t[MAXN << 2];

void build(int tl, int tr, int v) {
    if (tl == tr) {
        t[v] = a[tl];
    } else {
        int tm = (tl + tr) >> 1;
        build(tl, tm, v << 1);
        build(tm + 1, tr, v << 1 | 1);
        t[v] = max(t[v << 1], t[v << 1 | 1]);
    }
}

void upd(int tl, int tr, int v, int pos, int x) {
    if (tl == tr) {
        t[v] = x;
    } else {
        int tm = (tl + tr) >> 1;
        if (tm < pos)
            upd(tm + 1, tr, v << 1 | 1, pos, x);
        else
            upd(tl, tm, v << 1, pos, x);
        t[v] = max(t[v << 1], t[v << 1 | 1]);
    }
}
int get_max(int tl, int tr, int v, int l, int r) {
    if (l > r)
        return -INF;
    if (tl == l && tr == r)
        return t[v];
    int tm = (tl + tr) >> 1;
    return max(get_max(tl, tm, v << 1, l, min(tm, r)), get_max(tm + 1, tr, v << 1 | 1, max(tm + 1, l), r));
}

void solve() {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    build(0, n - 1, 1);

    while (q--) {
        int type, a, b;
        cin >> type >> a >> b;
        a--;
        if (type == 0) {
            upd(0, n - 1, 1, a, b);
        } else {
            if (get_max(0, n - 1, 1, a, n - 1) < b) {
                cout << -1 << '\n';
                continue;
            }

            int l = a - 1, r = n - 1;
            while (r - l > 1) {
                int m = (l + r) >> 1;
                if (get_max(0, n - 1, 1, a, m) >= b)
                    r = m;
                else
                    l = m;
            }
            cout << r + 1 << '\n';
        }
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