/**
 * Author: Monjur Hossain Khan, OpenAI Codex
 * License: CC0
 * Description: Compresses values in a vector to the range [1..k] by sorted order.
 * Time: O(n log n)
 * Status: tested
 */
#pragma once

template<class T>
void coordinateCompress(vector<T>& a) {
	int n = (int)a.size();
	if (n == 0) return;
	vector<pair<T, int>> pairs(n);
	for (int i = 0; i < n; ++i) {
		pairs[i] = {a[i], i};
	}
	sort(pairs.begin(), pairs.end());
	int nxt = 1;
	for (int i = 0; i < n; ++i) {
		if (i > 0 && pairs[i - 1].first != pairs[i].first) ++nxt;
		a[pairs[i].second] = nxt;
	}
}
