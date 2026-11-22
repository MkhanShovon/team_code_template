/**
 * Author: BUET_Orion (cp-algorithms)
 * Date: 2026-11-22
 * License: CC0
 * Description: Minkowski sum $\{p+q\}$ of two convex polygons given in ccw
 * order (no three collinear points). Result is convex, ccw, size $\le |P|+|Q|$.
 * Distance between convex polygons = distance from origin to $P \oplus (-Q)$.
 * Time: O(|P| + |Q|)
 * Status: stress-tested against convexHull of all sums
 */
#pragma once

#include "Point.h"

typedef Point<ll> P;
vector<P> minkowski(vector<P> A, vector<P> B) {
	for (auto* v : {&A, &B}) {
		rotate(v->begin(), min_element(vr(*v), [](P a, P b) {
			return make_pair(a.y, a.x) < make_pair(b.y, b.x); }), v->end());
		v->push_back((*v)[0]); v->push_back((*v)[1]);
	}
	vector<P> res; int i = 0, j = 0, n = len(A) - 2, m = len(B) - 2;
	while (i < n || j < m) {
		res.push_back(A[i] + B[j]);
		auto c = (A[i+1] - A[i]).cross(B[j+1] - B[j]);
		if (c >= 0 && i < n) ++i;
		if (c <= 0 && j < m) ++j;
	}
	return res;
}
