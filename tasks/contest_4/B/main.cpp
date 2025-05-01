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

void solve() {
    queue<int> q;
    string query;
    while (cin >> query) {
        if (query == "push") {
            int x;
            cin >> x;
            q.push(x);
            cout << "ok\n";
        } else if (query == "pop") {
            if (sz(q) == 0) {
                cout << "error\n";
            } else {
                cout << q.front() << '\n';
                q.pop();
            }
        } else if (query == "front") {
            if (sz(q) == 0) {
                cout << "error\n";
            } else {
                cout << q.front() << '\n';
            }
        } else if (query == "size") {
            cout << sz(q) << '\n';
        } else if (query == "clear") {
            while (!q.empty()) {
                q.pop();
            }
            cout << "ok\n";
        } else {
            cout << "bye\n";
            break;
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
