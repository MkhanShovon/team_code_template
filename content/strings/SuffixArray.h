/**
 * Author: SA-IS Paper / Unknown
 * Date: 2026-08-05
 * Description: O(N) Suffix Array construction using SA-IS (Induced Sorting).
 *  Builds Suffix Array(p), Inverse SA(pos), LCP array(lcp) and Sparse Table(st).
 * Time: O(N) for SA, O(N) for LCP, O(N log N) for Sparse Table Precomputation.
 *  O(|Pattern| log N) for pattern matching, O(1) for substring comparisons.
 */
#include <bits/stdc++.h>
using namespace std;

// --- SA-IS O(N) Helper Functions ---
void induced_sort(const vector<int>& vec, int val_range, vector<int>& SA, const vector<bool>& sl, const vector<int>& lms_idx) {
    vector<int> l(val_range, 0), r(val_range, 0);
    for (int c : vec) { if (c + 1 < val_range) ++l[c + 1]; ++r[c]; }
    partial_sum(l.begin(), l.end(), l.begin()); partial_sum(r.begin(), r.end(), r.begin());
    fill(SA.begin(), SA.end(), -1);
    for (int i = lms_idx.size() - 1; i >= 0; --i) SA[--r[vec[lms_idx[i]]]] = lms_idx[i];
    for (int i : SA) if (i >= 1 && sl[i - 1]) SA[l[vec[i - 1]]++] = i - 1;
    fill(r.begin(), r.end(), 0); for (int c : vec) ++r[c];
    partial_sum(r.begin(), r.end(), r.begin());
    for (int k = SA.size() - 1, i = SA[k]; k >= 1; --k, i = SA[k])
        if (i >= 1 && !sl[i - 1]) SA[--r[vec[i - 1]]] = i - 1;
}

vector<int> SA_IS(const vector<int>& vec, int val_range) {
    const int n = vec.size(); vector<int> SA(n), lms_idx; vector<bool> sl(n); sl[n - 1] = false;
    for (int i = n - 2; i >= 0; --i) {
        sl[i] = (vec[i] > vec[i + 1] || (vec[i] == vec[i + 1] && sl[i + 1]));
        if (sl[i] && !sl[i + 1]) lms_idx.push_back(i + 1);
    }
    reverse(lms_idx.begin(), lms_idx.end());
    induced_sort(vec, val_range, SA, sl, lms_idx);
    vector<int> new_lms_idx(lms_idx.size()), lms_vec(lms_idx.size());
    for (int i = 0, k = 0; i < n; ++i)
        if (!sl[SA[i]] && SA[i] >= 1 && sl[SA[i] - 1]) new_lms_idx[k++] = SA[i];
    int cur = 0; SA[n - 1] = cur;
    for (size_t k = 1; k < new_lms_idx.size(); ++k) {
        int i = new_lms_idx[k - 1], j = new_lms_idx[k];
        if (vec[i] != vec[j]) { SA[j] = ++cur; continue; }
        bool flag = false;
        for (int a = i + 1, b = j + 1;; ++a, ++b) {
            if (vec[a] != vec[b]) { flag = true; break; }
            if ((!sl[a] && sl[a - 1]) || (!sl[b] && sl[b - 1])) {
                flag = !((!sl[a] && sl[a - 1]) && (!sl[b] && sl[b - 1])); break;
            }
        }
        SA[j] = (flag ? ++cur : cur);
    }
    for (size_t i = 0; i < lms_idx.size(); ++i) lms_vec[i] = SA[lms_idx[i]];
    if (cur + 1 < (int)lms_idx.size()) {
        auto lms_SA = SA_IS(lms_vec, cur + 1);
        for (size_t i = 0; i < lms_idx.size(); ++i) new_lms_idx[i] = lms_idx[lms_SA[i]];
    }
    induced_sort(vec, val_range, SA, sl, new_lms_idx);
    return SA;
}

vector<int> get_suffix_array(const string& s, const int LIM = 128) {
    vector<int> vec(s.size() + 1); copy(begin(s), end(s), begin(vec)); vec.back() = '!';
    auto ret = SA_IS(vec, LIM); ret.erase(ret.begin());
    return ret;
}

// --- Main Blackbox Struct ---
struct SuffixArray {
    string s; int n;
    vector<int> p, pos, lcp, lg; // p=SA, pos=Inverse SA(rank), lcp=LCP array
    vector<vector<int>> st;      // Sparse Table for RMQ on LCP

    SuffixArray(string _s) {
        s = _s; n = s.size();
        p = get_suffix_array(s);  // O(N) SA Construction
        pos.resize(n); for (int i = 0; i < n; i++) pos[p[i]] = i;
        build_lcp(); build_st();
    }

    void build_lcp() { // Kasai's Algorithm O(N)
        lcp.resize(n - 1, 0);
        for (int i = 0, k = 0; i < n; i++) {
            if (pos[i] == n - 1) { k = 0; continue; }
            int j = p[pos[i] + 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
            lcp[pos[i]] = k;
            if (k) k--;
        }
    }

    void build_st() { // Sparse Table for RMQ O(N log N)
        if(n <= 1) return;
        lg.assign(n, 0); for (int i = 2; i < n; i++) lg[i] = lg[i / 2] + 1;
        st.assign(n - 1, vector<int>(20, 0));
        for (int i = 0; i < n - 1; i++) st[i][0] = lcp[i];
        for (int k = 1; k < 20; ++k)
            for (int i = 0; i + (1 << k) - 1 < n - 1; ++i)
                st[i][k] = min(st[i][k - 1], st[i + (1 << (k - 1))][k - 1]);
    }

    int query(int l, int r) { // minimum of lcp[l], ..., lcp[r]
        if (l > r) return 0;
        int k = lg[r - l + 1];
        return min(st[l][k], st[r - (1 << k) + 1][k]);
    }

    int get_lcp(int i, int j) { // lcp of suffix starting from i and j
        if (i == j) return n - i;
        int l = pos[i], r = pos[j];
        if (l > r) swap(l, r);
        return query(l, r - 1);
    }

    bool compare_sub(int l1, int r1, int l2, int r2) { // Lexicographical Compare O(1)
        int len1 = r1 - l1 + 1, len2 = r2 - l2 + 1, c = min({get_lcp(l1, l2), len1, len2});
        return (c < len1 && c < len2) ? s[l1 + c] < s[l2 + c] : len1 < len2;
    }

    // occurrences of s[p_idx, ..., p_idx + len - 1]
    pair<int, int> find_occurrence(int p_idx, int len) {
        int rnk = pos[p_idx], l = 0, r = rnk - 1; pair<int, int> ans = {rnk, rnk};
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (query(mid, rnk - 1) >= len) ans.first = mid, r = mid - 1;
            else l = mid + 1;
        }
        l = rnk + 1, r = n - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (query(rnk, mid - 1) >= len) ans.second = mid, l = mid + 1;
            else r = mid - 1;
        }
        return ans;
    }

    // Find custom pattern matching string bounds in O(|pat| * log N)
    pair<int, int> find_pattern(const string& pat) {
        int m = pat.size(), low = 0, high = n - 1, first = -1, last = -1;
        while (low <= high) { // Lower bound
            int mid = low + (high - low) / 2;
            if (s.compare(p[mid], min(n - p[mid], m), pat) >= 0) first = mid, high = mid - 1;
            else low = mid + 1;
        }
        if (first == -1 || s.compare(p[first], m, pat) != 0) return {-1, -1};
        low = 0, high = n - 1;
        while (low <= high) { // Upper bound
            int mid = low + (high - low) / 2;
            if (s.compare(p[mid], min(n - p[mid], m), pat) <= 0) last = mid, low = mid + 1;
            else high = mid - 1;
        }
        return {first, last};
    }
};

// --- Execution Example ---
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    string s = "abacaba";
    SuffixArray sa(s);
    
    // Example: Suffix Array output
    cout << "SA: ";
    for (int i = 0; i < s.size(); i++) cout << sa.p[i] << " ";
    cout << "\n";

    return 0;
}
