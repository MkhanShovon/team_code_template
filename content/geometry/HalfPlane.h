/**
 * Author: BUET_Orion (cp-algorithms)
 * Date: 2026-11-22
 * License: CC0
 * Description: Intersection of half-planes; each Line keeps the points to
 * the left of (or on) $a \to b$. Returns the vertices of the resulting convex
 * polygon in ccw order (may contain duplicate points), or empty if the
 * intersection is empty or degenerate. A big bounding box is added, so
 * unbounded results are clipped to it.
 * Time: O(n \log n)
 * Status: stress-tested against repeated polygonCut
 */
#pragma once

#include "Point.h"

typedef Point<double> P;
const double EPS = 1e-9;
struct Line {
	P p, d; double ang;
	Line(P a, P b) : p(a), d(b - a), ang(atan2(d.y, d.x)) {}
	bool out(P r) const { return d.cross(r - p) < -EPS; }
	P isect(const Line& o) const {
		return p + d * ((o.p - p).cross(o.d) / d.cross(o.d)); }
};
vector<P> hpIntersect(vector<Line> H, double inf = 1e9) {
	P box[4] = {P(inf, inf), P(-inf, inf), P(-inf, -inf), P(inf, -inf)};
	fl(i, 4) H.emplace_back(box[i], box[(i + 1) % 4]);
	sort(vr(H), [](auto& a, auto& b) { return a.ang < b.ang; });
	deque<Line> dq;
	for (auto& h : H) {
		while (len(dq) > 1 && h.out(dq.back().isect(dq[len(dq) - 2])))
			dq.pop_back();
		while (len(dq) > 1 && h.out(dq[0].isect(dq[1]))) dq.pop_front();
		if (len(dq) && fabs(h.d.cross(dq.back().d)) < EPS) {
			if (h.d.dot(dq.back().d) < 0) return {};
			if (!h.out(dq.back().p)) continue;
			dq.pop_back();
		}
		dq.push_back(h);
	}
	while (len(dq) > 2 && dq[0].out(dq.back().isect(dq[len(dq) - 2])))
		dq.pop_back();
	while (len(dq) > 2 && dq.back().out(dq[0].isect(dq[1])))
		dq.pop_front();
	if (len(dq) < 3) return {};
	vector<P> res;
	fl(i, len(dq)) res.push_back(dq[i].isect(dq[(i + 1) % len(dq)]));
	return res;
}
