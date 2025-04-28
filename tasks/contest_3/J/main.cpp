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

void solve() {
    string mode;
    cin >> mode;
    if (mode == "pack") {
        string s;
        cin >> s;
        int n = sz(s);
        // Build dictionary as a trie (prefix -> code)
        struct Node { int next[26]; Node() { for(int i=0;i<26;i++) next[i] = -1; } };
        vector<Node> dict;
        dict.reserve(n * 2);
        // Initialize dictionary with 'a'..'z'
        for (int i = 0; i < 26; ++i) {
            dict.push_back(Node());
        }
        int dict_size = 26;
        int code_width = 0;
        while ((1 << code_width) < dict_size) code_width++;
        if (code_width == 0) code_width = 1;
        int next_limit = 1 << code_width;
        vector<unsigned char> out_bytes;
        out_bytes.reserve(n);
        unsigned int bit_buffer = 0;
        int bit_count = 0;

        int prefix = s[0] - 'a';
        for (int i = 1; i < n; ++i) {
            int c = s[i] - 'a';
            if (dict[prefix].next[c] != -1) {
                prefix = dict[prefix].next[c];
            } else {
                // Output the code for prefix
                bit_buffer |= ((unsigned int)prefix << bit_count);
                bit_count += code_width;
                while (bit_count >= 8) {
                    out_bytes.push_back((unsigned char)(bit_buffer & 0xFF));
                    bit_buffer >>= 8;
                    bit_count -= 8;
                }
                // Add new string prefix+c to dictionary
                dict[prefix].next[c] = dict_size;
                dict.push_back(Node());
                dict_size++;
                if (dict_size == next_limit) {
                    code_width++;
                    next_limit <<= 1;
                }
                prefix = c;
            }
        }
        // Output the code for the last prefix
        bit_buffer |= ((unsigned int)prefix << bit_count);
        bit_count += code_width;
        while (bit_count >= 8) {
            out_bytes.push_back((unsigned char)(bit_buffer & 0xFF));
            bit_buffer >>= 8;
            bit_count -= 8;
        }
        // Write any remaining bits as a byte (pad with zeros)
        if (bit_count > 0) {
            out_bytes.push_back((unsigned char)(bit_buffer & 0xFF));
        }
        // Print result: number of bytes and each byte (0..255)
        cout << out_bytes.size();
        for (unsigned char b : out_bytes) {
            cout << " " << (int)b;
        }
        cout << endl;
        cout.flush();
    } else if (mode == "unpack") {
        int m;
        cin >> m;
        vector<unsigned char> in_bytes(m);
        for (int i = 0; i < m; ++i) {
            int x;
            cin >> x;
            in_bytes[i] = (unsigned char)x;
        }
        // Prepare dictionary for decompression
        vector<int> dict_prefix;
        vector<char> dict_char;
        dict_prefix.reserve(m * 2);
        dict_char.reserve(m * 2);
        for (int i = 0; i < 26; ++i) {
            dict_prefix.push_back(-1);
            dict_char.push_back((char)('a' + i));
        }
        int dict_size = 26;
        int code_width = 0;
        while ((1 << code_width) < dict_size) code_width++;
        if (code_width == 0) code_width = 1;
        int next_limit = 1 << code_width;
        unsigned int bit_buffer = 0;
        int bit_count = 0;
        int byte_index = 0;
        auto readCode = [&](int width) {
            while (bit_count < width && byte_index < (int)in_bytes.size()) {
                bit_buffer |= ((unsigned int)in_bytes[byte_index] << bit_count);
                bit_count += 8;
                byte_index++;
            }
            if (bit_count < width) return -1;
            unsigned int code = bit_buffer & ((1u << width) - 1);
            bit_buffer >>= width;
            bit_count -= width;
            return (int)code;
        };
        // Read first code
        int prev_code = readCode(code_width);
        if (prev_code >= 0 && prev_code < 26) {
            cout << (char)('a' + prev_code);
        }
        // Process remaining codes
        while (true) {
            if (dict_size == next_limit) {
                code_width++;
                next_limit <<= 1;
            }
            int curr_code = readCode(code_width);
            if (curr_code < 0) break;
            string entry;
            if (curr_code < dict_size) {
                int code = curr_code;
                string temp;
                while (code >= 26) {
                    temp.push_back(dict_char[code]);
                    code = dict_prefix[code];
                }
                temp.push_back((char)('a' + code));
                reverse(temp.begin(), temp.end());
                entry = temp;
            } else if (curr_code == dict_size) {
                // Special case: code equals dict_size (KwKwK case)
                int code = prev_code;
                string temp;
                while (code >= 26) {
                    temp.push_back(dict_char[code]);
                    code = dict_prefix[code];
                }
                temp.push_back((char)('a' + code));
                reverse(temp.begin(), temp.end());
                char firstChar = temp.back();
                entry = temp;
                entry.push_back(firstChar);
            } else {
                break;
            }
            cout << entry;
            char firstCharEntry = entry[0];
            dict_prefix.push_back(prev_code);
            dict_char.push_back(firstCharEntry);
            dict_size++;
            prev_code = curr_code;
        }
        cout << endl;
        cout.flush();
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