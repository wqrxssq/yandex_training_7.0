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
using pll = pair <ll, ll>;
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

struct node {
    ll h, color;
};

const int MAXN = 1e5;
const int power = 1e5 + 19;
int n;
int a[MAXN];
ll p[MAXN + 1];
ll precalc[MAXN + 1];
node t[MAXN << 2];

void init() {
    ll cur = 1;
    for (int i = 0; i <= n; i++) {
        p[i] = cur;
        cur *= power;
    }
    precalc[0] = 1;
    for (int i = 1; i <= n; i++)
        precalc[i] = precalc[i - 1] + p[i];
}

void push(node &v, node &vl, node &vr, int tl, int tm, int tr) {
    if (v.color == -1)
        return;
    vl = {v.color * precalc[tm - tl], v.color};
    vr = {v.color * precalc[tr - tm - 1], v.color};
    v.color = -1;
}
void build(int tl, int tr, int v) {
    if (tl == tr) {
        t[v] = {a[tl], -1};
    } else {
        int tm = (tl + tr) >> 1;
        build(tl, tm, v << 1);
        build(tm + 1, tr, v << 1 | 1);
        t[v] = {t[v << 1].h * p[tr - tm] + t[v << 1 | 1].h, -1};
    }
}
void upd(int tl, int tr, int v, int l, int r, ll c) {
    if (l > r)
        return;
    if (tl == l && tr == r) {
        t[v] = {c * precalc[tr - tl], c};
    } else {
        int tm = (tl + tr) >> 1;
        push(t[v], t[v << 1], t[v << 1 | 1], tl, tm, tr);
        upd(tl, tm, v << 1, l, min(tm, r), c);
        upd(tm + 1, tr, v << 1 | 1, max(tm + 1, l), r, c);
        t[v].h = t[v << 1].h * p[tr - tm] + t[v << 1 | 1].h;
    }
}
ll query(int tl, int tr, int v, int l, int r) {
    if (tl == l && tr == r)
        return t[v].h;
    int tm = (tl + tr) >> 1;
    push(t[v], t[v << 1], t[v << 1 | 1], tl, tm, tr);
    if (r <= tm)
        return query(tl, tm, v << 1, l, r);
    if (l > tm)
        return query(tm + 1, tr, v << 1 | 1, l, r);
    return query(tl, tm, v << 1, l, tm) * p[r - tm] + query(tm + 1, tr, v << 1 | 1, tm + 1, r);
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    init();
    build(0, n - 1, 1);
    int q;
    cin >> q;
    while (q--) {
        int type, l, r, k;
        cin >> type >> l >> r >> k;
        l--;
        r--;
        if (type == 0) {
            upd(0, n - 1, 1, l, r, k);
        } else {
            ll h1 = query(0, n - 1, 1, l, l + k - 1);
            ll h2 = query(0, n - 1, 1, r, r + k - 1);
            cout << (h1 == h2 ? '+' : '-');
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