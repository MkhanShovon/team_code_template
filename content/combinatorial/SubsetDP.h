/**
 * Author: Monjur Hossain Khan, OpenAI Codex
 * License: CC0
 * Description: Submask iteration and SOS DP (zeta/Mobius transforms).
 * The input size must be $2^K$.
 * Time: $O(K2^K)$
 * Status: tested
 */
#pragma once

// for (int sub = mask; sub; sub = (sub - 1) & mask) visits non-empty submasks.

template<class T>
void sosSubsets(vector<T>& f, bool inverse = false) {
	for (int b = 1; b < sz(f); b <<= 1)
		rep(mask,0,sz(f)) if (mask & b)
			f[mask] += (inverse ? -f[mask ^ b] : f[mask ^ b]);
}
template<class T>
void sosSupersets(vector<T>& f, bool inverse = false) {
	for (int b = 1; b < sz(f); b <<= 1)
		rep(mask,0,sz(f)) if (!(mask & b))
			f[mask] += (inverse ? -f[mask ^ b] : f[mask ^ b]);
}

// Inverse Transform (Mobius) - recover A from F (use inverse=true in sosSubsets/sosSupersets)
// for (int i = 0; i < (1<<N); i++) A[i] = F[i];
// for (int bit = 0; bit < N; bit++)
//     for (int mask = 0; mask < (1<<N); mask++)
//         if (mask & (1<<bit))
//             F[mask] -= F[mask ^ (1<<bit)];