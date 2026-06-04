/**
 * Author: Monjur Hossain Khan, OpenAI Codex
 * License: CC0
 * Description: Minimum excluded value (mex).
 * Time: O(n log n)
 * Status: tested
 */
#pragma once

long long mex(vector<long long> v) {
	sort(v.begin(), v.end());
	long long mx = 0;
	for (long long x : v) {
		if (x == mx) {
			++mx;
		} else if (x > mx) {
			break;
		}
	}
	return mx;
}
