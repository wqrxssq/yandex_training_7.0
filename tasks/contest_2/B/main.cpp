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
pii t[MAXN << 2];

pii combine(pii a, pii b) {
    if (a.ff > b.ff) {
        return a;
    } else {
        return b;
    }
}

void build(int tl, int tr, int v) {
    if (tl == tr) {
        t[v] = {a[tl], tl};
    } else {
        int tm = (tl + tr) >> 1;
        build(tl, tm, v << 1);
        build(tm + 1, tr, v << 1 | 1);
        t[v] = combine(t[v << 1], t[v << 1 | 1]);
    }
}

pii query(int tl, int tr, int v, int l, int r) {
    if (l > r) {
        return {-MOD, 0};
    }
    if (tl == l && tr == r) {
        return t[v];
    }
    int tm = (tl + tr) >> 1;
    return combine(query(tl, tm, v << 1, l, min(tm, r)), query(tm + 1, tr, v << 1 | 1, max(tm + 1, l), r));
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
        int l, r;
        cin >> l >> r;
        l--; r--;
        pii ans = query(0, n - 1, 1, l, r);
        cout << ans.ss + 1 << '\n';
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