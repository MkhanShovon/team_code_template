/**
 * Author: Adapted from CP-Algorithms
 * Date: 2026-08-05
 * Source: https://cp-algorithms.com/string/suffix-array.html
 * Description: O(N log N) Suffix Array construction using Prefix Doubling 
 *  and Counting Sort. Builds Suffix Array (p), Inverse Suffix Array (pos),
 *  LCP Array using Kasai's algorithm (lcp), and a Sparse Table (st) for 
 *  O(1) Range Minimum Queries on the LCP array.
 *  Suffixes are sorted lexicographically. 
 *  To get a common prefix between any two substrings, use get_lcp(i, j).
 * Time: O(N log N) for SA construction, O(N) for LCP, O(N log N) for Sparse Table. 
 *  O(|Pattern| log N) for pattern matching, O(1) for substring comparisons.
 */
#include <bits/stdc++.h>
using namespace std;

struct SuffixArray {
    string s;
    int n;
    vector<int> p;     // Suffix Array: sorted starting indices of suffixes
    vector<int> pos;   // Inverse Suffix Array: pos[i] is the rank of suffix starting at i
    vector<int> lcp;   // LCP Array: lcp[i] = LCP(p[i], p[i+1])
    vector<int> lg;    // Log precomputations for Sparse Table
    vector<vector<int>> st; // Sparse Table for O(1) RMQ

    // Constructor builds the entire environment
    SuffixArray(string text, char sentinel = '$') {
        s = text + sentinel;
        n = s.size();
        p.assign(n, 0);
        pos.assign(n, 0);
        lcp.assign(n, 0);
        
        build_suffix_array();
        build_lcp_array();
        build_sparse_table();
    }

    // 1. O(N log N) Suffix Array Construction (Optimized with Counting Sort)
    void build_suffix_array() {
        vector<int> c(n);
        
        // Step 0: Base case for length 1
        // We use counting sort for single characters to make it O(N)
        vector<pair<char, int>> a(n);
        for (int i = 0; i < n; i++) a[i] = {s[i], i};
        sort(a.begin(), a.end()); // sort for length 1 is fast enough, O(N log N) is fine here
        
        for (int i = 0; i < n; i++) p[i] = a[i].second;
        c[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            if (a[i].first == a[i - 1].first) c[p[i]] = c[p[i - 1]];
            else c[p[i]] = c[p[i - 1]] + 1;
        }

        // Loop for lengths 2, 4, 8... 
        int k = 0;
        while ((1 << k) < n) {
            // Smart Shift: Sort by the second element of the pair in O(N)
            // without actually doing a sort!
            for (int i = 0; i < n; i++) {
                p[i] = (p[i] - (1 << k) + n) % n;
            }

            // Counting Sort by the first element of the pair in O(N)
            count_sort(p, c);

            // Reassign classes (ranks)
            vector<int> c_new(n);
            c_new[p[0]] = 0;
            for (int i = 1; i < n; i++) {
                pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
                pair<int, int> now = {c[p[i]], c[(p[i] + (1 << k)) % n]};
                
                if (now == prev) c_new[p[i]] = c_new[p[i - 1]];
                else c_new[p[i]] = c_new[p[i - 1]] + 1;
            }
            c = c_new;
            k++;
        }
        
        // Build Inverse Suffix Array
        for (int i = 0; i < n; i++) pos[p[i]] = i;
    }

    // O(N) Counting Sort helper function
    void count_sort(vector<int>& p, vector<int>& c) {
        vector<int> cnt(n, 0);
        for (auto x : c) cnt[x]++;
        
        vector<int> pos_bucket(n);
        pos_bucket[0] = 0;
        for (int i = 1; i < n; i++) {
            pos_bucket[i] = pos_bucket[i - 1] + cnt[i - 1];
        }
        
        vector<int> p_new(n);
        for (auto x : p) {
            int i = c[x];
            p_new[pos_bucket[i]] = x;
            pos_bucket[i]++;
        }
        p = p_new;
    }

    // 2. O(N) LCP Array Construction (Kasai's Algorithm)
    void build_lcp_array() {
        int k = 0;
        for (int i = 0; i < n; i++) {
            int now = pos[i];
            if (now == 0) {
                k = 0;
                continue;
            }
            int prev = p[now - 1];
            while (i + k < n && prev + k < n && s[i + k] == s[prev + k]) k++;
            lcp[now - 1] = k; // Note: lcp[i] stores LCP(p[i], p[i+1])
            k = max(0, k - 1);
        }
    }

    // 3. Precompute Sparse Table for O(1) Range Minimum Queries
    void build_sparse_table() {
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;

        st.assign(n + 1, vector<int>(20, 0));
        for (int i = 0; i < n - 1; i++) st[i][0] = lcp[i];

        for (int j = 1; j < 20; j++) {
            for (int i = 0; i + (1 << j) <= n - 1; i++) {
                st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    // Query the structural LCP between any two suffixes starting at index i and j
    int get_lcp(int i, int j) {
        if (i == j) return n - i; // If same index, LCP is length of suffix from i
        int rankL = pos[i], rankR = pos[j];
        if (rankL > rankR) swap(rankL, rankR);
        rankR--; 
        int k = lg[rankR - rankL + 1];
        return min(st[rankL][k], st[rankR - (1 << k) + 1][k]);
    }

    // =========================================================================
    // COMMON PROBLEM APPLICATIONS
    // =========================================================================

    // APPLICATION 1: O(1) Lexicographical Substring Comparison
    // Returns true if S[l1...r1] < S[l2...r2]
    bool compare_substrings(int l1, int r1, int l2, int r2) {
        int len1 = r1 - l1 + 1;
        int len2 = r2 - l2 + 1;
        int common = get_lcp(l1, l2);
        int actual_common = min({common, len1, len2});

        if (actual_common < len1 && actual_common < len2) {
            return s[l1 + actual_common] < s[l2 + actual_common];
        }
        return len1 < len2; // The shorter prefix win strategy
    }

    // APPLICATION 2: O(|Pattern| * log N) Pattern Matching & Frequency Occurrence
    // Returns a pair representing the [low_rank, high_rank] index range in the Suffix Array
    // If the pattern does not exist, returns {-1, -1}
    pair<int, int> find_pattern_range(const string& pat) {
        int m = pat.size();
        
        // Lower bound binary search
        int low = 0, high = n - 1, first_idx = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (s.compare(p[mid], m, pat) >= 0) {
                first_idx = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        // Validate if pattern actually matches at the discovered position
        if (first_idx == -1 || s.compare(p[first_idx], m, pat) != 0) {
            return {-1, -1}; 
        }

        // Upper bound binary search
        low = 0, high = n - 1;
        int last_idx = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (s.compare(p[mid], m, pat) <= 0) {
                last_idx = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return {first_idx, last_idx};
    }

    // Counts how many times a pattern appears inside the text string
    int count_occurrences(const string& pat) {
        pair<int, int> range = find_pattern_range(pat);
        if (range.first == -1) return 0;
        return range.second - range.first + 1;
    }
};

// --- Execution Example ---
int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);

    string text = "abacaba";
    SuffixArray sa(text);

    // Problem 1: Substring Comparison
    // Substring 1: "aba" (0 to 2), Substring 2: "ba" (1 to 2)
    cout << "Is 'aba' < 'ba'? " << (sa.compare_substrings(0, 2, 1, 2) ? "Yes" : "No") << "\n";

    // Problem 2: Count pattern occurrences
    string pattern = "aba";
    cout << "Occurrences of '" << pattern << "': " << sa.count_occurrences(pattern) << "\n"; // Expected: 2

    return 0;
}
