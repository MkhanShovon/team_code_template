/**
 * Author: Monjur Hossain Khan, OpenAI Codex
 * License: CC0
 * Description: Computes nCr modulo any positive modulus by prime powers + CRT.
 * Time: O(\sqrt M + \sum p^q \log N)
 * Status: tested
 */
#pragma once

ll binPow(ll a, ll e, ll m) {
	ll r = 1 % m;
	for (a %= m; e; e >>= 1, a = (__int128)a * a % m)
		if (e & 1) r = (__int128)r * a % m;
	return r;
}
ll exgcd2(ll a, ll b, ll& x, ll& y) {
	if (!b) return x = 1, y = 0, a;
	ll d = exgcd2(b, a % b, y, x);
	return y -= a / b * x, d;
}
ll invModAny(ll a, ll m) {
	ll x, y, g = exgcd2(a, m, x, y);
	assert(g == 1);
	return (x % m + m) % m;
}
pair<ll, ll> crtSafe(ll a, ll m, ll b, ll n) {
	ll x, y, g = exgcd2(m, n, x, y);
	if ((b - a) % g) return {0, -1};
	ll l = m / g * n;
	ll t = (__int128)((b - a) / g) * x % (n / g);
	ll r = ((__int128)m * t + a) % l;
	if (r < 0) r += l;
	return {r, l};
}
ll countP(ll n, ll p) {
	ll r = 0;
	while (n) n /= p, r += n;
	return r;
}
ll factWithoutP(ll n, ll p, ll pk) {
	vector<ll> f(pk + 1, 1);
	rep(i,1,pk + 1) f[i] = f[i - 1] * (i % p ? i : 1) % pk;
	ll r = 1;
	while (n) {
		r = r * binPow(f[pk], n / pk, pk) % pk * f[n % pk] % pk;
		n /= p;
	}
	return r;
}
ll nCrPrimePower(ll n, ll k, ll p, int q) {
	if (k < 0 || k > n) return 0;
	ll pk = 1;
	rep(i,0,q) pk *= p;
	ll e = countP(n, p) - countP(k, p) - countP(n - k, p);
	if (e >= q) return 0;
	ll r = factWithoutP(n, p, pk);
	r = r * invModAny(factWithoutP(k, p, pk), pk) % pk;
	r = r * invModAny(factWithoutP(n - k, p, pk), pk) % pk;
	return r * binPow(p, e, pk) % pk;
}
ll nCrAnyMod(ll n, ll k, ll m) {
	if (m == 1) return 0;
	pair<ll, ll> ans = {0, 1};
	for (ll p = 2; p * p <= m; ++p) if (m % p == 0) {
		int q = 0; ll pk = 1;
		while (m % p == 0) m /= p, q++, pk *= p;
		ans = crtSafe(ans.first, ans.second, nCrPrimePower(n, k, p, q), pk);
	}
	if (m > 1) ans = crtSafe(ans.first, ans.second, nCrPrimePower(n, k, m, 1), m);
	return ans.first;
}
