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

const int alphabet_size = 26;
const int MAX_MASK = 255;

void solve() {
    string op;
    cin >> op;
    if (op == "pack") {
        string s;
        cin >> s;
        int n = sz(s);

        int initial_bits = 0;
        while ((1 << initial_bits) < alphabet_size) {
            initial_bits++;
        }
        int code_width = initial_bits;
        int next_code = alphabet_size;

        vector<array<int, alphabet_size>> dict_map;
        dict_map.reserve(n);
        for (int i = 0; i < alphabet_size; i++) {
            array<int,alphabet_size> arr;
            arr.fill(-1);
            dict_map.pb(arr);
        }

        uint64_t bit_buffer = 0;
        int bit_count = 0;
        vector<uint8_t> out_bytes;
        out_bytes.reserve(n / 2);

        int prefix = s[0] - 'a';
        for (int i = 1; i < n; i++) {
            int c = s[i] - 'a';
            int idx = dict_map[prefix][c];
            if (idx != -1) {
                prefix = idx;
            } else {
                bit_buffer |= (uint64_t)prefix << bit_count;
                bit_count += code_width;
                while (bit_count >= 8) {
                    out_bytes.pb(bit_buffer & MAX_MASK);
                    bit_buffer >>= 8;
                    bit_count -= 8;
                }
                dict_map[prefix][c] = next_code;
                array<int,alphabet_size> new_arr;
                new_arr.fill(-1);
                dict_map.pb(new_arr);
                next_code++;
                if (next_code == (1 << code_width)) {
                    code_width++;
                }
                prefix = c;
            }
        }
        bit_buffer |= (uint64_t)prefix << bit_count;
        bit_count += code_width;
        while (bit_count >= 8) {
            out_bytes.pb(bit_buffer & MAX_MASK);
            bit_buffer >>= 8;
            bit_count -= 8;
        }
        if (bit_count > 0) {
            out_bytes.pb(bit_buffer & MAX_MASK);
        }

        int N = sz(out_bytes);
        cout << N << '\n';
        for (int i = 0; i < N; i++) {
            cout << (int)out_bytes[i] << (i+1 < N ? ' ' : '\n');
        }
        cout << flush;

    } else if (op == "unpack") {
        int N;
        cin >> N;
        vector<uint8_t> data(N);
        for (int i = 0; i < N; i++) {
            int x;
            cin >> x;
            data[i] = (uint8_t)x;
        }

        int initial_bits = 0;
        while ((1 << initial_bits) < alphabet_size) {
            initial_bits++;
        }
        int code_width = initial_bits;
        int next_code = alphabet_size;

        vector<pair<int,char>> dict_rev;
        dict_rev.reserve(N);
        for (int i = 0; i < alphabet_size; i++) {
            dict_rev.emplace_back(-1, char('a' + i));
        }

        uint64_t bit_buffer = 0;
        int bit_count = 0, pos = 0;
        auto read_code = [&]() -> int {
            while (bit_count < code_width && pos < N) {
                bit_buffer |= (uint64_t)data[pos++] << bit_count;
                bit_count += 8;
            }
            if (bit_count < code_width) return -1;
            int code = bit_buffer & ((1 << code_width) - 1);
            bit_buffer >>= code_width;
            bit_count -= code_width;
            return code;
        };

        auto reconstruct = [&](int code) {
            string tmp;
            while (code != -1) {
                tmp.push_back(dict_rev[code].second);
                code = dict_rev[code].first;
            }
            reverse(tmp.begin(), tmp.end());
            return tmp;
        };

        int first_code = read_code();
        if (first_code < 0) return;
        string w = reconstruct(first_code);
        string result;
        result.reserve(2 * N);
        result += w;
        int prev_code = first_code;

        while (true) {
            int code = read_code();
            if (code < 0) break;
            string entry;
            if (code < next_code) {
                entry = reconstruct(code);
            } else if (code == next_code) {
                entry = w + w[0];
            } else {
                break;
            }
            result += entry;
            dict_rev.emplace_back(prev_code, entry[0]);
            next_code++;
            if (next_code == ((1 << code_width) - 1)) {
                code_width++;
            }
            prev_code = code;
            w = entry;
        }

        cout << result << '\n' << flush;
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
