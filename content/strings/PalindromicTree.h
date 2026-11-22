/**
 * Author: BUET_Orion (adapted from youknowwho)
 * Date: 2026-11-22
 * License: CC0
 * Description: Palindromic tree (eertree). Node 0 is the root of length -1,
 * node 1 the empty string; every other node is a distinct palindromic
 * substring (count = len(L) - 2). link[v] = longest proper palindromic
 * suffix. After add(i), last = longest palindromic suffix of s[0..i].
 * After occ(), cnt[v] = number of occurrences of node v in s.
 * Usage: Eertree t(s); fl(i, len(s)) t.add(i); t.occ();
 * Time: O(N)
 * Status: stress-tested
 */
#pragma once

struct Eertree {
	string s; vector<array<int, 26>> nx; vll L, link, cnt;
	int last = 1;
	Eertree(const string& s) : s(s) { node(-1, 0); node(0, 0); }
	int node(int l, int lk) {
		nx.push_back({}); L.push_back(l); link.push_back(lk);
		cnt.push_back(0); return len(L) - 1;
	}
	int get(int v, int i) {
		while (i - L[v] - 1 < 0 || s[i - L[v] - 1] != s[i]) v = link[v];
		return v;
	}
	void add(int i) {
		int c = s[i] - 'a', v = get(last, i);
		if (!nx[v][c]) {
			int lk = L[v] == -1 ? 1 : nx[get(link[v], i)][c];
			int u = node(L[v] + 2, lk); nx[v][c] = u;
		}
		cnt[last = nx[v][c]]++;
	}
	void occ() { for (int v = len(L); --v > 1;) cnt[link[v]] += cnt[v]; }
};
