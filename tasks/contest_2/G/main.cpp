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

struct node {
    int ans, pref, suf;
    int tl, tr;
};

const int MAXN = 5e5;
int n;
int a[MAXN];
node t[MAXN << 2];

node combine(node l, node r) {
    node res;
    res.ans = max(max(l.ans, r.ans), l.suf + r.pref);
    res.pref = (l.pref == l.tr - l.tl + 1 ? l.pref + r.pref : l.pref);
    res.suf = (r.suf == r.tr - r.tl + 1 ? r.suf + l.suf : r.suf);
    res.tl = l.tl;
    res.tr = r.tr;
    return res;
}

void build(int tl, int tr, int v) {
    if (tl == tr) {
        t[v] = {a[tl] == 0, a[tl] == 0, a[tl] == 0, tl, tl};
    } else {
        int tm = (tl + tr) >> 1;
        build(tl, tm, v << 1);
        build(tm + 1, tr, v << 1 | 1);
        t[v] = combine(t[v << 1], t[v << 1 | 1]);
    }
}
void upd(int tl, int tr, int v, int pos, int x) {
    if (tl == tr) {
        t[v] = {x == 0, x == 0, x == 0, tl, tl};
    } else {
        int tm = (tl + tr) >> 1;
        if (pos > tm)
            upd(tm + 1, tr, v << 1 | 1, pos, x);
        else
            upd(tl, tm, v << 1, pos, x);
        t[v] = combine(t[v << 1], t[v << 1 | 1]);
    }
}
node query(int tl, int tr, int v, int l, int r) {
    if (tl == l && tr == r)
        return t[v];
    int tm = (tl + tr) >> 1;
    if (r <= tm)
        return query(tl, tm, v << 1, l, r);
    if (l > tm)
        return query(tm + 1, tr, v << 1 | 1, l, r);
    return combine(query(tl, tm, v << 1, l, tm), query(tm + 1, tr, v << 1 | 1, tm + 1, r));
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    build(0, n - 1, 1);
    int q;
    cin >> q;
    while (q--) {
        string type;
        cin >> type;
        if (type[0] == 'U') {
            int pos, x;
            cin >> pos >> x;
            upd(0, n - 1, 1, pos - 1, x);
        } else {
            int l, r;
            cin >> l >> r;
            cout << query(0, n - 1, 1, l - 1, r - 1).ans << '\n';
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