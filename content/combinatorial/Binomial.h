/**
 * Author: BUET_Orion
 * Date: 2026-11-22
 * License: CC0
 * Description: nCr modulo a prime via factorials; lucas() for huge n, k
 * (when n $\geq$ mod). combExact: exact nCr while it fits in ll.
 * $\binom{n}{k}$ is odd iff $k \,\&\, n = k$.
 * Time: O(N) preprocessing, O(1) per C, O(\log_p N) per lucas.
 * Status: tested
 */
#pragma once

struct Comb {
	ll mod; vector<ll> f, fi;
	Comb(int n, ll mod = 1e9 + 7) : mod(mod), f(n + 1, 1), fi(n + 1, 1) {
		fls(i, 1, n) f[i] = f[i - 1] * i % mod;
		for (ll e = mod - 2, b = f[n]; e; e /= 2, b = b * b % mod)
			if (e & 1) fi[n] = fi[n] * b % mod;
		for (int i = n; i > 0; i--) fi[i - 1] = fi[i] * i % mod;
	}
	ll C(ll n, ll k) {
		if (k < 0 || k > n) return 0;
		return f[n] * fi[k] % mod * fi[n - k] % mod;
	}
	ll lucas(ll n, ll k) { // needs Comb(mod - 1, mod)
		ll r = 1;
		for (; n || k; n /= mod, k /= mod) r = r * C(n % mod, k % mod) % mod;
		return r;
	}
};
ll combExact(ll n, ll k) {
	if (k < 0 || k > n) return 0;
	ll r = 1; k = min(k, n - k);
	fls(i, 1, k) r = r * (n - k + i) / i;
	return r;
}
