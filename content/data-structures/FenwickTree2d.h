/**
 * Author: Simon Lindholm
 * Date: 2017-05-11
 * License: CC0
 * Source: folklore
 * Description: Computes sums a[i,j] for all i<I, j<J, and increases single elements a[i,j].
 *  Requires that the elements to be updated are known in advance (call fakeUpdate() before init()).
 * Time: $O(\log^2 N)$. (Use persistent segment trees for $O(\log N)$.)
 * Status: stress-tested
 */
#pragma once

#include "FenwickTree.h"

struct FT2 {
	vector<vll> ys; vector<FT> ft;
	FT2(int limx) : ys(limx) {}
	void fakeUpdate(int x, int y) {
		for (; x < len(ys); x |= x + 1) ys[x].push_back(y);
	}
	void init() {
		for (vll& v : ys) sort(vr(v)), v.erase(unique(vr(v)), v.end()), ft.emplace_back(len(v));
	}
	int ind(int x, int y) {
		return (int)(lower_bound(vr(ys[x]), y) - ys[x].begin()); }
	void update(int x, int y, ll dif) {
		for (; x < len(ys); x |= x + 1)
			ft[x].update(ind(x, y), dif);
	}
	ll query(int x, int y) {
		ll sum = 0;
		for (; x; x &= x - 1)
			sum += ft[x-1].query(ind(x-1, y));
		return sum;
	}
	ll query_range(int x1, int y1, int x2, int y2)
    {
        if (x1 > x2 or y1 > y2) return 0;
        return query(x2 + 1, y2 + 1) - query(x1, y2 + 1) - query(x2 + 1, y1) + query(x1, y1);
    }
};
