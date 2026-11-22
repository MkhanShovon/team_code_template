/**
 * Author: BUET_Orion
 * Date: 2026-10-20
 * License: CC0
 * Description: Suffix automaton of s. A state = set of substrings with the
 * same end-positions; len = longest one, link = suffix link, firstpos = end
 * (1-indexed) of first occurrence. Walk nx from 0 to find a pattern p;
 * then cnt(u) = \#occurrences, first start = firstpos - |p|.
 * dist() = \#distinct substrings, kth(k) = k-th (1-indexed) distinct
 * substring in lexicographic order, lcs(w) = longest common substring.
 * Usage: SuffixAutomaton sa(s);
 * Time: O(N \log \Sigma)
 * Status: tested
 */
#pragma once

struct SuffixAutomaton {
	struct St { int len = 0, link = -1, firstpos = 0, pre = 0; map<char,int> nx; };
	vector<St> t; vll term; vector<ll> dp, paths; vector<vll> g; int last = 0;
	SuffixAutomaton(const string& s) : t(1) {
		for (char c : s) extend(c);
		dp.assign(len(t), -1); g.resize(len(t));
		for (auto& x : t) term.push_back(x.pre);
		fls(i, 1, len(t) - 1) g[t[i].link].push_back(i);
	}
	void extend(char c) {
		int cur = len(t), p = last; t.emplace_back(); t[cur].len = t[last].len + 1;
		t[cur].firstpos = t[cur].len; t[cur].pre = 1;
		for (; p != -1 && !t[p].nx.count(c); p = t[p].link) t[p].nx[c] = cur;
		if (p == -1) t[cur].link = 0;
		else {
			int q = t[p].nx[c];
			if (t[p].len + 1 == t[q].len) t[cur].link = q;
			else {
				int cl = len(t); t.push_back(t[q]);
				t[cl].len = t[p].len + 1, t[cl].pre = 0;
				for (; p != -1 && t[p].nx[c] == q; p = t[p].link) t[p].nx[c] = cl;
				t[q].link = t[cur].link = cl;
			}
		}
		last = cur;
	}
	ll cnt(int i) { // occurrences of state i
		if (dp[i] != -1) return dp[i];
		ll r = term[i]; for (int x : g[i]) r += cnt(x);
		return dp[i] = r;
	}
	ll dist() {
		ll r = 0; fls(i, 1, len(t) - 1) r += t[i].len - t[t[i].link].len;
		return r;
	}
	string kth(ll k) {
		if (paths.empty()) {
			vll ord(len(t)); iota(vr(ord), 0); paths.assign(len(t), 1);
			sort(vr(ord), [&](int a, int b) { return t[a].len > t[b].len; });
			for (int u : ord) for (auto [c, v] : t[u].nx) paths[u] += paths[v];
		}
		string res; int u = 0;
		while (k > 0) for (auto [c, v] : t[u].nx) {
			if (k <= paths[v]) { res += c; k--; u = v; break; }
			k -= paths[v];
		}
		return res;
	}
	int lcs(const string& w) {
		int v = 0, l = 0, b = 0;
		for (char c : w) {
			while (v && !t[v].nx.count(c)) v = t[v].link, l = t[v].len;
			if (t[v].nx.count(c)) v = t[v].nx[c], l++;
			b = max(b, l);
		}
		return b;
	}
};
