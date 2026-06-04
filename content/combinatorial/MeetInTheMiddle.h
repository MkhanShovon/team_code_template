/**
 * Author: Monjur Hossain Khan, OpenAI Codex
 * License: CC0
 * Description: Count subset pairs whose two half-sums add to 0 modulo m.
 * Time: $O(n2^{n/2})$
 * Status: untested
 */
#pragma once

long long countSubsetPairsMod(const vector<long long>& v, long long m) {
	int n = (int)v.size();
	auto get_subset_sums = [&](int l, int r) {
		if (l > r) return vector<long long>{0};
		int len = r - l + 1;
		vector<long long> res;
		res.reserve(1 << len);
		for (int mask = 0; mask < (1 << len); ++mask) {
			long long sum = 0;
			for (int j = 0; j < len; ++j) {
				if (mask & (1 << j)) sum += v[l + j];
			}
			res.push_back(sum % m);
		}
		return res;
	};

	auto left = get_subset_sums(0, n / 2 - 1);
	auto right = get_subset_sums(n / 2, n - 1);

	sort(right.begin(), right.end());

	long long ans = 0;
	for (long long i : left) {
		long long target = (m - i) % m;
		auto range = equal_range(right.begin(), right.end(), target);
		ans += (long long)(range.second - range.first);
	}
	return ans;
}
