/**
 * Author: Monjur Hossain Khan, OpenAI Codex
 * License: CC0
 * Description: Solves $ax+by=c$ and counts solutions in a rectangle.
 * Time: O(\log \min(a,b))
 * Status: tested
 */
#pragma once

#include "euclid.h"

ll floorDiv(ll a, ll b) {
	assert(b);
	if (b < 0) a = -a, b = -b;
	return a >= 0 ? a / b : -((-a + b - 1) / b);
}
ll ceilDiv(ll a, ll b) { return -floorDiv(-a, b); }

bool diophantine(ll a, ll b, ll c, ll& x, ll& y, ll& g) {
	if (!a && !b) return g = 0, x = y = 0, c == 0;
	g = euclid(abs(a), abs(b), x, y);
	if (c % g) return false;
	x *= c / g; y *= c / g;
	if (a < 0) x = -x;
	if (b < 0) y = -y;
	return true;
}
ll countDiophantine(ll a, ll b, ll c, ll minx, ll maxx, ll miny, ll maxy) {
	ll x, y, g;
	if (!diophantine(a, b, c, x, y, g)) return 0;
	if (!a && !b) return (maxx - minx + 1) * (maxy - miny + 1);
	if (!a) return miny <= y && y <= maxy ? maxx - minx + 1 : 0;
	if (!b) return minx <= x && x <= maxx ? maxy - miny + 1 : 0;
	ll lo = LLONG_MIN / 4, hi = LLONG_MAX / 4;
	auto add = [&](ll val, ll step, ll L, ll R) {
		if (step > 0) lo = max(lo, ceilDiv(L - val, step)),
			hi = min(hi, floorDiv(R - val, step));
		else lo = max(lo, ceilDiv(R - val, step)),
			hi = min(hi, floorDiv(L - val, step));
	};
	add(x, b / g, minx, maxx);
	add(y, -a / g, miny, maxy);
	return max(0LL, hi - lo + 1);
}
