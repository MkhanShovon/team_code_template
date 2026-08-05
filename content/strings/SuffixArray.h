/**
 * Author: SA-IS Paper Authors / Custom
 * Date: 2026-08-05
 * Source: Ge Nong, Sen Zhang, Wai Hong Chan
 * Description: O(N) Suffix Array construction using SA-IS (Induced Sorting).
 *  Builds Suffix Array (p), Inverse SA (pos), LCP array (lcp) using Kasai, 
 *  and Sparse Table (st) for RMQ. 
 *  Includes O(1) lexicographical substring compare `comp_sub`, O(log N) internal 
 *  pattern occurrence `find_occ`, and O(|P| log N) pattern search `find_pat`.
 * Time: O(N) for SA & LCP, O(N log N) for Sparse Table, O(1) RMQ.
 * Status: stress-tested a bit
 */
#include <bits/stdc++.h>
using namespace std;

// --- SA-IS O(N) Core ---
void induced_sort(const vector<int> &vec, int val_range, vector<int> &SA, const vector<bool> &sl, const vector<int> &lms_idx) {
    vector<int> l(val_range, 0), r(val_range, 0);
    for (int c : vec) { if (c + 1 < val_range) ++l[c + 1]; ++r[c]; }
    partial_sum(l.begin(), l.end(), l.begin()); partial_sum(r.begin(), r.end(), r.begin());
    fill(SA.begin(), SA.end(), -1);
    for (int i = lms_idx.size() - 1; i >= 0; --i) SA[--r[vec[lms_idx[i]]]] = lms_idx[i];
    for (int i : SA) if (i >= 1 && sl[i - 1]) SA[l[vec[i - 1]]++] = i - 1; // Sort L-types
    fill(r.begin(), r.end(), 0); for (int c : vec) ++r[c];
    partial_sum(r.begin(), r.end(), r.begin());
    for (int k = SA.size() - 1, i = SA[k]; k >= 1; --k, i = SA[k]) 
        if (i >= 1 && !sl[i - 1]) SA[--r[vec[i - 1]]] = i - 1; // Sort S-types
}

vector<int> SA_IS(const vector<int> &vec, int val_range) {
    const int n = vec.size(); vector<int> SA(n), lms_idx; vector<bool> sl(n); sl[n - 1] = false;
    for (int i = n - 2; i >= 0; --i) { // Classify types & find LMS nodes
        sl[i] = (vec[i] > vec[i + 1] || (vec[i] == vec[i + 1] && sl[i + 1]));
        if (sl[i] && !sl[i + 1]) lms_idx.push_back(i + 1);
    }
    reverse(lms_idx.begin(), lms_idx.end()); induced_sort(vec, val_range, SA, sl, lms_idx);
    vector<int> new_lms_idx(lms_idx.size()), lms_vec(lms_idx.size());
    for (int i = 0, k = 0; i < n; ++i) if (!sl[SA[i]] && SA[i] >= 1 && sl[SA[i] - 1]) new_lms_idx[k++] = SA[i];
    int cur = 0; SA[n - 1] = cur;
    for (size_t k = 1; k < new_lms_idx.size(); ++k) { // Rename LMS substrings
        int i = new_lms_idx[k - 1], j = new_lms_idx[k];
        if (vec[i] != vec[j]) { SA[j] = ++cur; continue; }
        bool flag = false;
        for (int a = i + 1, b = j + 1;; ++a, ++b) {
            if (vec[a] != vec[b]) { flag = true; break; }
            if ((!sl[a] && sl[a - 1]) || (!sl[b] && sl[b - 1])) { flag = !((!sl[a] && sl[a - 1]) && (!sl[b] && sl[b - 1])); break; }
        }
        SA[j] = (flag ? ++cur : cur);
    }
    for (size_t i = 0; i < lms_idx.size(); ++i) lms_vec[i] = SA[lms_idx[i]];
    if (cur + 1 < (int)lms_idx.size()) { // Recursive call if not unique
        auto lms_SA = SA_IS(lms_vec, cur + 1);
        for (size_t i = 0; i < lms_idx.size(); ++i) new_lms_idx[i] = lms_idx[lms_SA[i]];
    }
    induced_sort(vec, val_range, SA, sl, new_lms_idx); return SA;
}

struct SuffixArray {
    string s; int n;
    vector<int> p, pos, lcp, lg; vector<vector<int>> st;
    SuffixArray(string text, char sentinel = '$') {
        s = text + sentinel; n = s.size(); pos.assign(n, 0); lcp.assign(n, 0);
        vector<int> vec(n); for (int i = 0; i < n; i++) vec[i] = s[i];
        p = SA_IS(vec, 256); // 1. Build SA in O(N)
        for (int i = 0; i < n; i++) pos[p[i]] = i;
        for (int i = 0, k = 0; i < n; i++) { // 2. Build LCP (Kasai) in O(N)
            if (pos[i] == 0) { k = 0; continue; }
            int j = p[pos[i] - 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
            lcp[pos[i] - 1] = k; k = max(0, k - 1);
        }
        lg.assign(n + 1, 0); for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
        st.assign(n + 1, vector<int>(20, 0)); for (int i = 0; i < n - 1; i++) st[i][0] = lcp[i];
        for (int j = 1; j < 20; j++) for (int i = 0; i + (1 << j) <= n - 1; i++) // 3. Build RMQ in O(N log N)
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }
    int query(int l, int r) { // Min LCP in range [l, r]
        if (l > r) return 0;
        int k = lg[r - l + 1]; return min(st[l][k], st[r - (1 << k) + 1][k]);
    }
    int get_lcp(int i, int j) { // LCP of suffixes starting at i and j in O(1)
        if (i == j) return n - i;
        int l = pos[i], r = pos[j]; if (l > r) swap(l, r); return query(l, r - 1);
    }
    bool comp_sub(int l1, int r1, int l2, int r2) { // Lexicographical compare O(1)
        int len1 = r1 - l1 + 1, len2 = r2 - l2 + 1, c = min({get_lcp(l1, l2), len1, len2});
        return (c < len1 && c < len2) ? s[l1 + c] < s[l2 + c] : len1 < len2;
    }
    pair<int, int> find_pat(const string& pat) { // Find SA range of pattern O(|P| log N)
        int m = pat.size(), l = 0, r = n - 1, f = -1, lst = -1;
        while (l <= r) { // Lower bound
            int mid = l + (r - l) / 2;
            if (s.compare(p[mid], m, pat) >= 0) f = mid, r = mid - 1; else l = mid + 1;
        }
        if (f == -1 || s.compare(p[f], m, pat) != 0) return {-1, -1};
        l = 0, r = n - 1;
        while (l <= r) { // Upper bound
            int mid = l + (r - l) / 2;
            if (s.compare(p[mid], m, pat) <= 0) lst = mid, l = mid + 1; else r = mid - 1;
        }
        return {f, lst};
    }
    int count_pat(const string& pat) { // Frequency of external pattern
        auto r = find_pat(pat); return r.first == -1 ? 0 : r.second - r.first + 1;
    }
    pair<int, int> find_occ(int idx, int len) { // SA range of internal substring O(log N)
        int rnk = pos[idx], l = 0, r = rnk - 1; pair<int, int> ans = {rnk, rnk};
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (query(mid, rnk - 1) >= len) ans.first = mid, r = mid - 1; else l = mid + 1;
        }
        l = rnk + 1, r = n - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (query(rnk, mid - 1) >= len) ans.second = mid, l = mid + 1; else r = mid - 1;
        }
        return ans;
    }
};

int main() {
    SuffixArray sa(s);
    int match_len = sa.get_lcp(2, 5);              // LCP
    bool is_less = sa.comp_sub(1, 3, 4, 6);        // Substring compare
    string pat = "abc";
    int freq1 = sa.count_pat(pat);               // outsider pattern
    pair<int, int> range = sa.find_pat(pat);     //{first_rank, last_rank}
    auto range = sa.find_occ(0, 3);                // substring of s
    int freq2 = range.second - range.first + 1;
    return 0;
}
