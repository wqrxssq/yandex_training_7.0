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

string code(string s) {
    int n = (int)s.size();
    string res;
    for (int i = 0, pos = 1, j; i < n; pos += j) {
        res.push_back('0');
        for (j = 1; j < pos && i < n; i++, j++)
            res.push_back(s[i]);
    }
     
    for (int pos = 1; pos <= (int)res.size(); pos <<= 1) {
        for (int i = pos; i <= (int)res.size(); i += pos)
            for (int j = 0; j < pos && i <= (int)res.size(); j++, i++)
                res[pos - 1] = ((res[pos - 1] - '0') ^ (res[i - 1] - '0')) + '0';
    }
     
    return res;
}
 
string decode(string res) {
    int sum = 0;
    for (int pos = 1; pos <= (int)res.size(); pos <<= 1) {
        int check = 0;
        for (int i = pos; i <= (int)res.size(); i += pos)
            for (int j = 0; j < pos && i <= (int)res.size(); j++, i++)
                check = (check ^ res[i - 1] - '0');
        if (check)
            sum += pos;
    }
    if (sum)
        res[sum - 1] = (res[sum - 1] == '1' ? '0' : '1');
     
    string s;
    for (int i = 1; i <= (int)res.size(); i++)
        if (i & (i - 1))
            s.push_back(res[i - 1]);
    return s;
}
 
void solve() {
    int type;
    string s;
    cin >> type >> s;
    if (type == 1)
        cout << code(s) << '\n';
    else
        cout << decode(s) << '\n';
}

int main() {
    fast_input;
#ifdef __APPLE__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    solve();
}