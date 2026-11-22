/**
 * Author: Monjur Hossain Khan, OpenAI Codex
 * License: CC0
 * Description: Remove intervals contained in an earlier/outer interval.
 * Input and output use inclusive intervals. Output is sorted by left endpoint.
 * Time: O(N \log N)
 * Status: tested
 */
#pragma once

vector<pair<ll, ll>> eliminateNestedRanges(vector<pair<ll, ll>> ranges) {
	sort(vr(ranges), [](pair<ll, ll> a, pair<ll, ll> b) {
		return a.first == b.first ? a.second > b.second : a.first < b.first;
	});
	vector<pair<ll, ll>> res;
	int bestR = INT_MIN;
	for (pair<ll, ll> p : ranges) if (p.second > bestR) {
		res.push_back(p);
		bestR = p.second;
	}
	return res;
}
