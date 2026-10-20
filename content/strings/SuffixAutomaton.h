#include <bits/stdc++.h>
using namespace std;

struct SuffixAutomaton {
    struct node {
        int len, link, firstpos; // len: max length, link: suffix link, firstpos: 1-indexed first occurrence end pos
        map<char, int> nxt;      // nxt: automaton transitions
    };
    
    int sz, last; vector<node> t; vector<int> term; vector<long long> dp, paths; vector<vector<int>> g;
    // Initialization. Time: O(N) to allocate vector memory
    SuffixAutomaton(int n) : sz(1), last(0), t(2 * n), term(2 * n, 0), dp(2 * n, -1), paths(2 * n, 0), g(2 * n) { t[0].link = -1; }
    
    // Time: Amortized O(log K) due to map operations. (O(1) if array was used instead of map)
    void extend(char c) {
        int p = last;
        if (t[p].nxt.count(c)) { // Handle pre-existing transitions (e.g., Trie -> SAM)
            int q = t[p].nxt[c]; if (t[q].len == t[p].len + 1) { last = q; return; }
            int cl = sz++; t[cl] = t[q]; t[cl].len = t[p].len + 1; t[q].link = cl; last = cl;
            for (; p != -1 && t[p].nxt[c] == q; p = t[p].link) t[p].nxt[c] = cl; return;
        }
        int cur = sz++; t[cur].len = t[last].len + 1; t[cur].firstpos = t[cur].len; p = last;
        for (; p != -1 && !t[p].nxt.count(c); p = t[p].link) t[p].nxt[c] = cur;
        if (p == -1) t[cur].link = 0;
        else {
            int q = t[p].nxt[c];
            if (t[p].len + 1 == t[q].len) t[cur].link = q;
            else {
                int cl = sz++; t[cl] = t[q]; t[cl].len = t[p].len + 1;
                for (; p != -1 && t[p].nxt[c] == q; p = t[p].link) t[p].nxt[c] = cl;
                t[q].link = t[cur].link = cl;
            }
        }
        last = cur;
    }
    
    // Time: O(N log K) to build the automaton and the suffix link tree
    void build(string &s) { for(char c : s) { extend(c); term[last] = 1; } for(int i = 1; i < sz; i++) g[t[i].link].push_back(i); }
    
    // Frequency of state i. Time: O(N) total across all states due to memoization on Suffix Link Tree
    long long cnt(int i) { 
        if(dp[i] != -1) return dp[i]; long long r = term[i]; for(int x : g[i]) r += cnt(x); return dp[i] = r;
    }
    
    // Total distinct substrings. Time: O(N) iterating through at most 2N states
    long long dist() { 
        long long r = 0; for (int i = 1; i < sz; i++) r += t[i].len - t[t[i].link].len; return r; 
    }
    
    // Precalculate DP for finding K-th substring. Time: O(N log N) because of std::sort (can be optimized to O(N) with counting sort)
    void calc_paths() { 
        vector<int> ord(sz - 1); iota(ord.begin(), ord.end(), 1); 
        sort(ord.begin(), ord.end(), [&](int a, int b) { return t[a].len > t[b].len; }); // Topological sort by len
        for (int i = 0; i < sz; i++) paths[i] = 1; paths[0] = 0;
        for (int u : ord) for (auto &[c, v] : t[u].nxt) paths[u] += paths[v];
        for (auto &[c, v] : t[0].nxt) paths[0] += paths[v];
    }
    
    // Find K-th lexicographically smallest distinct substring. Time: O(L * K) where L is the length of the result
    string kth(long long k) { 
        if (!paths[0]) calc_paths(); string res = ""; int u = 0;
        while (k > 0) {
            for (auto &[c, v] : t[u].nxt) { // Map iteration preserves lexicographical order
                if (k <= paths[v]) { res += c; k--; u = v; break; } 
                k -= paths[v];
            }
        } return res;
    }
    
    // Length of Longest Common Substring with 'w'. Time: O(|W| log K) where |W| is length of query string w
    int lcs(string &w) { 
        int v = 0, l = 0, b = 0; 
        for (char c : w) {
            while (v && !t[v].nxt.count(c)) { v = t[v].link; l = t[v].len; }
            if (t[v].nxt.count(c)) { v = t[v].nxt[c]; l++; } 
            b = max(b, l);
        } return b;
    }
};

int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    string s = "ababa";
    SuffixAutomaton sa(s.size()); sa.build(s);

    // 1. Number of distinct non-empty substrings: a,b,ab,ba,aba,bab,abab,baba,ababa
    cout << "distinct: " << sa.dist() << '\n';                 // 9

    // 2. Pattern lookup: walk transitions from root; -1 if p is not a substring
    auto find = [&](const string &p) { int u = 0; for (char c : p) { if (!sa.t[u].nxt.count(c)) return -1; u = sa.t[u].nxt[c]; } return u; };
    for (string p : {"aba", "ba", "abc"}) {
        int u = find(p);
        if (u == -1) { cout << p << ": not found\n"; continue; }
        cout << p << ": occurrences = " << sa.cnt(u)                            // aba -> 2, ba -> 2
             << ", first index = " << sa.t[u].firstpos - (int)p.size() << '\n'; // 0-indexed start: aba -> 0, ba -> 1
    }

    // 3. K-th lexicographically smallest distinct substring (1-indexed, need k <= dist())
    // order: a, ab, aba, abab, ababa, b, ba, bab, baba
    cout << "kth(3): " << sa.kth(3) << '\n';                   // aba
    cout << "kth(6): " << sa.kth(6) << '\n';                   // b

    // 4. Longest common substring length with another string
    string w = "xbabz";
    cout << "lcs with " << w << ": " << sa.lcs(w) << '\n';     // 3 ("bab")
    return 0;
}