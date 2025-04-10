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

struct event {
    int diff;
    int res_if_even, res_if_odd;
};

bool cmp(event& a, event& b) {
    return a.diff < b.diff;
}

const int MAXN = 1e5;
int n;
deque<event> even_lenght;
deque<event> odd_lenght;

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int cnt_even = 0, cnt_odd = 0;
        for (int j = 0; j < sz(s); j++) {
            if (j & 1) {
                cnt_odd += s[j] == 'S';
            } else {
                cnt_even += s[j] == 'S';
            }
        }
        if (sz(s) & 1) {
            odd_lenght.pb({cnt_even - cnt_odd, cnt_even, cnt_odd});
        } else {
            even_lenght.pb({cnt_even - cnt_odd, cnt_even, cnt_odd});
        }
    }

    sort(all(even_lenght), cmp);
    sort(all(odd_lenght), cmp);

    ll res = 0;

    while (!even_lenght.empty() && even_lenght.back().diff >= 0) {
        res += even_lenght.back().res_if_even;
        even_lenght.pop_back();
    }

    if (odd_lenght.empty()) {
        while (!even_lenght.empty()) {
            res += even_lenght.back().res_if_even;
            even_lenght.pop_back();
        }
        cout << res << '\n';
        return;
    }

    res += odd_lenght.back().res_if_even;
    odd_lenght.pop_back();

    while (!even_lenght.empty()) {
        res += even_lenght.back().res_if_odd;
        even_lenght.pop_back();
    }

    bool is_odd_pos = true;
    while (!odd_lenght.empty()) {
        if (is_odd_pos) {
            res += odd_lenght.front().res_if_odd;
            odd_lenght.pop_front();
        } else {
            res += odd_lenght.back().res_if_even;
            odd_lenght.pop_back();
        }
        is_odd_pos ^= 1;
    }

    cout << res << '\n';
}

int main() {
    fast_input;
#ifdef __APPLE__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    solve();
}