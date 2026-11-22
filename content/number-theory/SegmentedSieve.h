/**
 * Author: BUET_Orion
 * Date: 2026-11-22
 * License: CC0
 * Description: isP[i] is true iff $L+i$ is prime, for $0 \le L \le R$.
 * Works for $R \approx 10^{12}$ with $R-L \approx 10^7$.
 * Time: O((R-L)\log\log R + \sqrt R)
 * Status: stress-tested
 */
#pragma once

vector<bool> segSieve(ll L, ll R) {
	ll lim = sqrtl(R) + 1;
	vector<bool> mark(lim + 1), isP(R - L + 1, 1);
	for (ll i = 2; i <= lim; i++) if (!mark[i]) {
		for (ll j = i * i; j <= lim; j += i) mark[j] = 1;
		for (ll j = max(i * i, (L + i - 1) / i * i); j <= R; j += i)
			isP[j - L] = 0;
	}
	for (ll x = L; x <= min(R, 1LL); x++) isP[x - L] = 0;
	return isP;
}
