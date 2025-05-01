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

const int MAXN = 2e5;
int n;
int timer = 1;
list<pii> a;
int ans[MAXN];

list<pii>::iterator get_left(list<pii>::iterator it) {
    if (it == a.begin()) {
        return prev(a.end());
    }
    return --it;
}

list<pii>::iterator get_right(list<pii>::iterator it) {
    if (it == prev(a.end())) {
        return a.begin();
    }
    return ++it;
}

bool is_week(list<pii>::iterator it) {
    if (ans[it->ss] != 0) {
        return false;
    }

    auto left = get_left(it);
    auto right = get_right(it);

    // cout << left->ss << ' ' << right->ss << ' ' << it->ss << '\n';
    return (it->ff < left->ff && it->ff < right->ff);
}

void remove_week_and_get_candidats(list<pii>::iterator it, vector<list<pii>::iterator>& cand) {
    if (ans[it->ss] == 0) {
        cand.push_back(get_left(it));
        cand.push_back(get_right(it));
        ans[it->ss] = timer;
        a.erase(it);
    }
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.push_back({x, i});
    }

    vector<list<pii>::iterator> candidats;
    for (auto it = a.begin(); it != a.end(); it++) {
        if (is_week(it)) {
            candidats.pb(it);
        }
    }

    while (!candidats.empty() && sz(a) > 2) {
        vector<list<pii>::iterator> need_to_remove;
        vector<list<pii>::iterator> new_candidats;
        for (auto it : candidats) {
            if (is_week(it)) {
                need_to_remove.pb(it);
            }
        }

        for (auto it : need_to_remove) {
            remove_week_and_get_candidats(it, new_candidats);
        }
        candidats = new_candidats;
        timer++;
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
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
