/**
 * Author: BUET_Orion
 * Date: 2026-11-22
 * License: CC0
 * Description: SOS DP (zeta transform) on $2^K$ masks, len(f) = $2^K$.
 * sosSub: f[m] = sum of f[s] over submasks s of m. sosSup: over supermasks.
 * inv = true gives the inverse (Mobius) transform. Under a modulus, reduce
 * after each step. E.g. # of i with a[i] \& x = 0 is sub[~x \& (2^K-1)] of freq.
 * Time: O(K 2^K)
 * Status: tested
 */
#pragma once

template<class T> void sosSub(vector<T>& f, bool inv = 0) {
	for (int b = 1; b < len(f); b *= 2) fl(m, len(f)) if (m & b)
		f[m] += inv ? -f[m ^ b] : f[m ^ b];
}
template<class T> void sosSup(vector<T>& f, bool inv = 0) {
	for (int b = 1; b < len(f); b *= 2) fl(m, len(f)) if (!(m & b))
		f[m] += inv ? -f[m ^ b] : f[m ^ b];
}
