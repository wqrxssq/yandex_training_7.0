#include <iostream>
#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
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
#include <list>
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
#define fast_input ios_base::sync_with_stdio(0); cin.tie(0)
#define setpr cout << setprecision(6) << fixed

const int MAXN = 10000;
int n;
int s[MAXN], p[MAXN];

void init() {
    for (int i = 0; i < n; i++) {
        s[i] = 1;
        p[i] = i;
    }
}

int leader(int v) {
    return (v == p[v] ? v : p[v] = leader(p[v]));
}

void unite(int v, int u) {
    v = leader(v); u = leader(u);
    if (v == u) 
        return;
    if (s[v] < s[u]) { // need s(v) > s(u)
        swap(v, u);
    }
    s[v] += s[u];
    p[u] = v;
}

bool is_connected() {
    int v = rand() % n;
    return s[leader(v)] == n;
}

void solve() {
    int m;
    cin >> n >> m;
    init();

    if (n == 1) {
        cout << 0 << '\n';
        return;
    }

    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        v--; u--;
        unite(v, u);
        if (is_connected()) {
            cout << i + 1 << '\n';
            return;
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
    return 0;
}
