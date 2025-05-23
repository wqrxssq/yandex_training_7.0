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

const int MAXN = 1e5;
int n;
int a[MAXN];
ll t[MAXN << 2];

void build(int tl, int tr, int v) {
    if (tl == tr) {
        t[v] = a[tl];
    } else {
        int tm = (tl + tr) >> 1;
        build(tl, tm, v << 1);
        build(tm + 1, tr, v << 1 | 1);
    }
}

ll get(int tl, int tr, int v, int pos) {
    if (tl == tr) {
        return t[v];
    }
    int tm = (tl + tr) >> 1;
    if (pos <= tm) {
        return get(tl, tm, v << 1, pos) + t[v];
    } else {
        return get(tm + 1, tr, v << 1 | 1, pos) + t[v];
    }
}

void add(int tl, int tr, int v, int l, int r, int x) {
    if (l > r) {
        return;
    }
    if (tl == l && tr == r) {
        t[v] += x;
    } else {
        int tm = (tl + tr) >> 1;
        add(tl, tm, v << 1, l, min(tm, r), x);
        add(tm + 1, tr, v << 1 | 1, max(tm + 1, l), r, x);
    }
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    build(0, n - 1, 1);

    int q;
    cin >> q;
    while (q--) {
        char type;
        cin >> type;
        if (type == 'g') {
            int pos;
            cin >> pos;
            pos--;
            cout << get(0, n - 1, 1, pos) << '\n';
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            l--; r--;
            add(0, n - 1, 1, l, r, x);
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