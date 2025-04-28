#include <iostream>
#include <algorithm>
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

struct Edge {
    int to;
    ll cap;
    int rev;
    Edge(int _to, ll _cap, int _rev) : to(_to), cap(_cap), rev(_rev) {}
};

class MaxFlow {
public:
    int N;
    vector<vector<Edge>> graph;
    MaxFlow(int n): N(n), graph(n) {}

    void addEdge(int u, int v, ll c) {
        graph[u].emplace_back(v, c, graph[v].size());
        graph[v].emplace_back(u, 0, graph[u].size() - 1);
    }

    ll maxFlow(int s, int t) {
        ll flow = 0;
        vector<int> level(N), it(N);
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            queue<int> q; q.push(s);
            while (!q.empty() && level[t] < 0) {
                int u = q.front(); q.pop();
                for (auto &e : graph[u]) {
                    if (level[e.to] < 0 && e.cap > 0) {
                        level[e.to] = level[u] + 1;
                        q.push(e.to);
                    }
                }
            }
            if (level[t] < 0) break;
            fill(it.begin(), it.end(), 0);
            while (true) {
                ll pushed = dfs(s, t, LLONG_MAX, level, it);
                if (pushed <= 0) break;
                flow += pushed;
            }
        }
        return flow;
    }

private:
    ll dfs(int u, int t, ll f, vector<int>& level, vector<int>& it) {
        if (u == t) return f;
        for (int &i = it[u]; i < (int)graph[u].size(); ++i) {
            Edge &e = graph[u][i];
            if (e.cap > 0 && level[e.to] == level[u] + 1) {
                ll got = dfs(e.to, t, min(f, e.cap), level, it);
                if (got > 0) {
                    e.cap -= got;
                    graph[e.to][e.rev].cap += got;
                    return got;
                }
            }
        }
        return 0;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<ull> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int m = 0;
    vector<int> cnt(n, 0);
    for (int i = 0; i < n; ++i) {
        ull x = a[i];
        if (x) {
            m = max(m, 64 - __builtin_clzll(x));
            cnt[i] = __builtin_popcountll(x);
        }
    }

    ll S = 0;
    for (int c : cnt) S += c;
    if (S % 2 == 1) {
        cout << "impossible\n";
        return;
    }
    ll P = S / 2;
    if (P > 1LL * (n/2) * m) {
        cout << "impossible\n";
        return;
    }
    if (m == 0) {

        for (int i = 0; i < n; ++i) {
            cout << 0 << " ";
        }
        cout << '\n';
        return;
    }

    int base = P / m;
    int rem  = P % m;
    vector<int> need(m);
    for (int j = 0; j < m; ++j) {
        int pairs = base + (j < rem ? 1 : 0);
        need[j] = 2 * pairs;
    }

    int SRC = 0;
    int SINK = n + m + 1;
    MaxFlow mf(SINK + 1);

    for (int i = 0; i < n; ++i) {
        if (cnt[i] > 0) {
            mf.addEdge(SRC, 1 + i, cnt[i]);
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            mf.addEdge(1 + i, 1 + n + j, 1);
        }
    }
    for (int j = 0; j < m; ++j) {
        if (need[j] > 0) {
            mf.addEdge(1 + n + j, SINK, need[j]);
        }
    }

    ll flow = mf.maxFlow(SRC, SINK);
    if (flow != S) {
        cout << "impossible\n";
        return;
    }

    vector<ull> b(n, 0ULL);
    for (int i = 0; i < n; ++i) {
        for (auto &e : mf.graph[1 + i]) {
            if (e.to >= 1 + n && e.to <= n + m && e.cap == 0) {
                int col = e.to - (1 + n);
                b[i] |= (1ULL << col);
            }
        }
    }

    ull xall = 0;
    for (ull v : b) xall ^= v;
    if (xall != 0ULL) {
        cout << "impossible\n";
        return;
    }

    for (int i = 0; i < n; ++i) {
        cout << b[i] << " ";
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
    return 0;
}