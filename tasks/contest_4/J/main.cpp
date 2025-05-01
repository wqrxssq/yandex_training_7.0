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

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

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

using ordered_set = tree<pll, null_type, less<pll>, rb_tree_tag, tree_order_statistics_node_update>;

const int MAXN = 100000;
const ll GAP = 1e12;
int n;
int a[MAXN];

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int k;
    cin >> k;

    ordered_set q;

    ll s = 0;

    for (int i = 0; i < n; i++) {
        q.insert({ 1LL * i * GAP, a[i] });
        s += 1LL * a[i] * a[i];
    }

    cout << s << '\n';

    while (k--) {
        int type, v;
        cin >> type >> v;
        v--;

        auto it = q.find_by_order(v);
        auto [id, len] = *it;

        q.erase(it);
        s -= len * len;

        if (type == 1) {
            bool hasL = (!q.empty() && v > 0);
            bool hasR = (!q.empty() && v < sz(q));
            if (hasL && hasR) {
                ll x1 = len >> 1;
                ll x2 = len - x1;

                auto itL = q.find_by_order(v - 1);
                auto [posL, lenL] = *itL;
                q.erase(itL);
                s -= lenL * lenL;
                lenL += x1;
                s += lenL * lenL;
                q.insert({ posL, lenL });

                auto itR = q.find_by_order(v);
                auto [posR, lenR] = *itR;
                q.erase(itR);
                s -= lenR * lenR;
                lenR += x2;
                s += lenR * lenR;
                q.insert({ posR, lenR });
            } else if (hasL) {
                auto itL = q.find_by_order(v - 1);
                auto [posL, lenL] = *itL;
                q.erase(itL);
                s -= lenL * lenL;
                lenL += len;
                s += lenL * lenL;
                q.insert({ posL, lenL });
            } else if (hasR) {
                auto itR = q.find_by_order(v);
                auto [posR, lenR] = *itR;
                q.erase(itR);
                s -= lenR * lenR;
                lenR += len;
                s += lenR * lenR;
                q.insert({ posR, lenR });
            }
        } else {
            ll keyL = (v > 0) ? q.find_by_order(v - 1)->first : id - MAXN * 2;
            ll keyR = (v < sz(q)) ? q.find_by_order(v)->first : id + MAXN * 2;

            ll k1 = keyL + (id - keyL) / 2;
            ll k2 = id + (keyR - id) / 2;

            ll x1 = len / 2;
            ll x2 = len - x1;
            pll left = { k1, x1 };
            pll right = { k2, x2 };
            q.insert(left);
            q.insert(right);
            s += x1 * x1 + x2 * x2;
        }

        cout << s << "\n";
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
