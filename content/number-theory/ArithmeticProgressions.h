/**
 * Author: Monjur Hossain Khan, OpenAI Codex
 * License: CC0
 * Description: Intersects two arithmetic progressions $a_1+d_1x$ and
 * $a_2+d_2x$. Returns {first, step}; step 0 means empty.
 * Time: O(\log \min(d_1,d_2))
 * Status: tested
 */
#pragma once

#include "euclid.h"

pair<ll, ll> intersectAP(ll a1, ll d1, ll a2, ll d2) {
	ll x, y, g = euclid(d1, d2, x, y);
	if ((a2 - a1) % g) return {0, 0};
	ll l = d1 / g * d2;
	ll t = (__int128)((a2 - a1) / g) * x % (d2 / g);
	ll a = ((__int128)d1 * t + a1) % l;
	if (a < 0) a += l;
	ll st = max(a1, a2);
	if (a < st) a += ((st - a + l - 1) / l) * l;
	return {a, l};
}
