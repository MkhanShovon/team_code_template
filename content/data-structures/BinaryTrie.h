/**
 * Author: Monjur Hossain Khan, OpenAI Codex
 * License: CC0
 * Description: Binary trie for maximum xor queries over non-negative integers.
 * Time: O(B) per insert/query.
 * Status: tested
 */
#pragma once

template<int B = 30>
struct BinaryTrie {
	struct Node { int ch[2] = {-1, -1}, cnt = 0; };
	vector<Node> t{{}};
	void insert(int x) {
		int v = 0; t[v].cnt++;
		for (int b = B; b >= 0; --b) {
			int c = (x >> b) & 1;
			if (t[v].ch[c] == -1) t[v].ch[c] = sz(t), t.push_back({});
			v = t[v].ch[c]; t[v].cnt++;
		}
	}
	int maxXor(int x) {
		assert(t[0].cnt);
		int v = 0, ans = 0;
		for (int b = B; b >= 0; --b) {
			int c = (x >> b) & 1, go = t[v].ch[c ^ 1];
			if (go != -1 && t[go].cnt) ans |= 1 << b, v = go;
			else v = t[v].ch[c];
		}
		return ans;
	}
};
