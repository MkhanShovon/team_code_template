/**
 * Author: Simon Lindholm
 * Date: 2016-09-06
 * License: CC0
 * Source: own work
 * Description: A hash map with a custom hash to avoid getting hacked on
 *   Codeforces. \texttt{gp\_hash\_table} is 3-5x faster than \texttt{unordered\_map}.
 *   The \texttt{chash} below uses a large odd constant multiplied by the input, then
 *   byte-swapped, which gives good distribution. For pair keys use \texttt{pair\_hash}.
 *   For Codeforces, also XOR with a random value to defend against anti-hash tests.
 * Time: O(1) amortized
 * Status: tested on Kattis
 */
#pragma once

#include <bits/extc++.h> /** keep-include */
using namespace __gnu_pbds;
using namespace std;

struct chash {
	const uint64_t C = ll(4e18 * acos(0)) | 71; // large odd number
	ll operator()(ll x) const { return __builtin_bswap64(x * C); }
};
gp_hash_table<ll, int, chash> h;

/** For Codeforces, or other places where hacking might be a problem:

const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
	const uint64_t C = ll(4e18 * acos(0)) | 71; // large odd number
	ll operator()(ll x) const { return __builtin_bswap64((x^RANDOM)*C); }
};
gp_hash_table<ll, int, chash> h({},{},{},{},{1<<16});
*/

struct pair_hash {
	template<class A, class B>
	size_t operator()(const pair<A, B>& p) const {
		size_t seed = hash<A>{}(p.first);
		seed ^= hash<B>{}(p.second) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		return seed;
	}
};
// gp_hash_table<pair<ll, ll>, ll, pair_hash> mp;
