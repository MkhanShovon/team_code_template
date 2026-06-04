/**
 * Author: Monjur Hossain Khan, OpenAI Codex
 * License: CC0
 * Description: Computes $a[l]^{(a[l+1]^{(\cdots)})}$ modulo $m$ for a range,
 * using phi reduction while preserving "large enough" exponents.
 * Time: O((r-l+1)\sqrt m \log m)
 * Status: tested
 */
#pragma once

ll phiSingle(ll n) {
	ll r = n;
	for (ll p = 2; p * p <= n; ++p) if (n % p == 0) {
		while (n % p == 0) n /= p;
		r = r / p * (p - 1);
	}
	if (n > 1) r = r / n * (n - 1);
	return r;
}
ll liftMod(__int128 x, ll m) { return x < m ? (ll)x : (ll)(x % m + m); }
ll powLift(ll a, ll e, ll m) {
	ll r = liftMod(1, m);
	for (a = liftMod(a, m); e; e >>= 1, a = liftMod((__int128)a * a, m))
		if (e & 1) r = liftMod((__int128)r * a, m);
	return r;
}
ll powerTowerLift(const vector<ll>& a, int l, int r, ll m) {
	if (m == 1) return 1;
	if (l == r) return liftMod(a[l], m);
	return powLift(a[l], powerTowerLift(a, l + 1, r, phiSingle(m)), m);
}
ll powerTowerMod(const vector<ll>& a, int l, int r, ll m) {
	return powerTowerLift(a, l, r, m) % m;
}
