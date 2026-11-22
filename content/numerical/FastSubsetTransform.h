/**
 * Author: Lucian Bicsi
 * Date: 2015-06-25
 * License: GNU Free Documentation License 1.2
 * Source: csacademy
 * Description: Transform to a basis with fast convolutions of the form
 * $\displaystyle c[z] = \sum\nolimits_{z = x \oplus y} a[x] \cdot b[y]$,
 * where $\oplus$ is one of AND, OR, XOR. The size of $a$ must be a power of two.
 * Time: O(N \log N)
 * Status: stress-tested
 */
#pragma once

void FST(vll& a, bool inv) {
	for (int n = len(a), step = 1; step < n; step *= 2) {
		for (int i = 0; i < n; i += 2 * step) fls(j, i, i+step - 1) {
			ll &u = a[j], &v = a[j + step]; tie(u, v) =
				inv ? pair<ll, ll>(v - u, u) : pair<ll, ll>(v, u + v); // AND
				// inv ? pair<ll, ll>(v, u - v) : pair<ll, ll>(u + v, u); // OR /// include-line
				// pair<ll, ll>(u + v, u - v);                   // XOR /// include-line
		}
	}
	// if (inv) for (int& x : a) x /= len(a); // XOR only /// include-line
}
vll conv(vll a, vll b) {
	FST(a, 0); FST(b, 0);
	fl(i, len(a)) a[i] *= b[i];
	FST(a, 1); return a;
}
