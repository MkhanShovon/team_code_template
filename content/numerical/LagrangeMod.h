/**
 * Author: BUET_Orion (adapted from youknowwho)
 * Date: 2026-11-22
 * License: CC0
 * Description: Given $y_i = f(i)$ for $i = 0..n-1$ of a polynomial of degree
 * $< n$, returns $f(x) \bmod p$ ($p$ prime, $p \geq n$). E.g.\
 * $\sum_{i=1}^{m} i^k$ is a polynomial in $m$ of degree $k+1$: feed $k+2$ values.
 * Time: O(n + \log p)
 * Status: stress-tested
 */
#pragma once

#include "../number-theory/ModPow.h"

ll lagrange(const vector<ll>& y, ll x) {
	int n = len(y); x = (x % mod + mod) % mod;
	vector<ll> pre(n + 1, 1), suf(n + 1, 1), fi(n, 1);
	fl(i, n) pre[i+1] = pre[i] * ((x - i + mod) % mod) % mod;
	for (int i = n; i--;) suf[i] = suf[i+1] * ((x - i + mod) % mod) % mod;
	ll f = 1, res = 0;
	fls(i, 1, n - 1) f = f * i % mod;
	fi[n-1] = modpow(f, mod - 2);
	for (int i = n - 1; i > 0; i--) fi[i-1] = fi[i] * i % mod;
	fl(i, n) {
		ll t = y[i] * pre[i] % mod * suf[i+1] % mod * fi[i] % mod
			* fi[n-1-i] % mod;
		res = (res + ((n - 1 - i) & 1 ? mod - t : t)) % mod;
	}
	return res;
}
