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

struct node {
    int sum;
    node *next;

    node() : sum(0), next(NULL) {}
};

const int MAXN = 2e5 + 1;
node* r[MAXN];

node* pop_el(node *parent) {
    node* v = parent->next;
    return v;
}
node* push_el(node *parent, int x) {
    node* v = new node();
    v->next = parent;
    v->sum += v->next->sum + x;
    return v;
}

void solve() {
    r[0] = new node();
    int q;
    cin >> q;
    ll ans = 0;
    for (int i = 0; i < q; i++) {
        int id, x;
        cin >> id >> x;
        if (x == 0)
            r[i + 1] = pop_el(r[id]);
        else
            r[i + 1] = push_el(r[id], x);
        ans += r[i + 1]->sum;
    }
    cout << ans << '\n';
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
