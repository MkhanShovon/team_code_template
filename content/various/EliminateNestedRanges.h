/**
 * Author: Monjur Hossain Khan, OpenAI Codex
 * License: CC0
 * Description: Remove intervals contained in an earlier/outer interval.
 * Input and output use inclusive intervals. Output is sorted by left endpoint.
 * Time: O(N \log N)
 * Status: tested
 */
#pragma once

vector<pii> eliminateNestedRanges(vector<pii> ranges) {
	sort(all(ranges), [](pii a, pii b) {
		return a.first == b.first ? a.second > b.second : a.first < b.first;
	});
	vector<pii> res;
	int bestR = INT_MIN;
	for (pii p : ranges) if (p.second > bestR) {
		res.push_back(p);
		bestR = p.second;
	}
	return res;
}
