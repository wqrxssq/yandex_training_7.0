#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

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
#define fast_input ios_base::sync_with_stdio(0); cin.tie(0)
#define setpr cout << setprecision(6) << fixed

const int MAXN = 1e5;
int n;
int a[MAXN];
ll t[MAXN];

void upd(int id, int x) {
    int delta = x - a[id];
    a[id] = x;
    for (int i = id; i < n; i |= i + 1)
        t[i] += delta;
}
ll sum(int r) {
    ll res = 0;
    for (int i = r; i > -1; i = (i & (i + 1)) - 1)
        res += t[i];
    return res;
}
ll sum(int l, int r) {
    return sum(r) - sum(l - 1);
}

void solve() {
    int k;
    cin >> n >> k;

    while (k--) {
        char type;
        cin >> type;
        if (type == 'A') {
            int pos, x;
            cin >> pos >> x;
            pos--;
            upd(pos, x);
        } else {
            int l, r;
            cin >> l >> r;
            l--; r--;
            cout << sum(l, r) << '\n';
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