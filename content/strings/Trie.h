/**
 * Author: Monjur Hossain Khan, OpenAI Codex
 * License: CC0
 * Description: Trie for lowercase strings with counts and erase.
 * Time: O(|S|)
 * Status: tested
 */
#pragma once

struct Trie {
	enum {alpha = 26, first = 'a'};
	struct Node {
		int next[alpha], pref = 0, term = 0;
		Node() { memset(next, -1, sizeof next); }
	};
	vector<Node> t{Node()};
	void insert(const string& s) {
		int v = 0; t[v].pref++;
		for (char ch : s) {
			int c = ch - first;
			if (t[v].next[c] == -1) t[v].next[c] = sz(t), t.emplace_back();
			v = t[v].next[c]; t[v].pref++;
		}
		t[v].term++;
	}
	int find(const string& s) const {
		int v = 0;
		for (char ch : s) {
			int c = ch - first;
			if (t[v].next[c] == -1) return -1;
			v = t[v].next[c];
		}
		return v;
	}
	int countWord(const string& s) const {
		int v = find(s);
		return v == -1 ? 0 : t[v].term;
	}
	int countPrefix(const string& s) const {
		int v = find(s);
		return v == -1 ? 0 : t[v].pref;
	}
	bool erase(const string& s) {
		if (!countWord(s)) return false;
		int v = 0; t[v].pref--;
		for (char ch : s) v = t[v].next[ch - first], t[v].pref--;
		t[v].term--;
		return true;
	}
};
