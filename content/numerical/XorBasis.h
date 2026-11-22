/**
 * Author: BUET_Orion (adapted from youknowwho)
 * Date: 2026-11-22
 * License: CC0
 * Description: Linear basis of non-negative integers over GF(2).
 * insert returns false if x was already representable; r = rank,
 * number of distinct subset xors = $2^r$. kth: k-th smallest
 * (0-indexed, $k < 2^r$) subset xor; the empty subset gives 0.
 * Time: O(B) per insert/query, O(B^2) for kth
 * Status: stress-tested
 */
#pragma once

struct XorBasis {
	static const int B = 61;
	ll b[B] = {}; int r = 0;
	bool insert(ll x) {
		for (int i = B; i--;) if (x >> i & 1) {
			if (!b[i]) return b[i] = x, ++r;
			x ^= b[i];
		}
		return 0;
	}
	bool can(ll x) { for (int i = B; i--;) x = min(x, x ^ b[i]); return !x; }
	ll maxXor(ll x = 0) { for (int i = B; i--;) x = max(x, x ^ b[i]); return x; }
	ll kth(ll k) {
		vector<ll> v; ll res = 0;
		fl(i, B) if (b[i]) {
			for (int j = i; j--;) if (b[i] >> j & 1) b[i] ^= b[j];
			v.push_back(b[i]);
		}
		fl(j, len(v)) if (k >> j & 1) res ^= v[j];
		return res;
	}
};
