/**
 * Author: Monjur Hossain Khan, OpenAI Codex
 * License: CC0
 * Description: Assign distinct random 64-bit labels to values, useful for
 * randomized/Zobrist-style hashing of sets, multisets, or colors.
 * Time: O(N \log N)
 * Status: tested
 */
#pragma once

template<class T>
map<T, uint64_t> randomLabels(vector<T> v) {
	sort(all(v));
	v.erase(unique(all(v)), v.end());
	mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
	map<T, uint64_t> mp;
	set<uint64_t> used = {0};
	for (T x : v) {
		uint64_t y;
		do y = rng(); while (used.count(y));
		used.insert(y);
		mp[x] = y;
	}
	return mp;
}
