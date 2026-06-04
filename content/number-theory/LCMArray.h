/**
 * Author: Monjur Hossain Khan, OpenAI Codex
 * License: CC0
 * Description: LCM of an array, capped at limit + 1 to avoid overflow.
 * Time: O(N \log A)
 * Status: tested
 */
#pragma once

ll lcmArrayCap(const vector<ll>& v, ll limit) {
	__int128 L = 1;
	for (ll x : v) {
		ll g = gcd((ll)min<__int128>(L, LLONG_MAX), x);
		L = L / g * x;
		if (L > limit) return limit + 1;
	}
	return (ll)L;
}
