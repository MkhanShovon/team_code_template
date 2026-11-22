/**
 * Author: Simon Lindholm
 * Date: 2016-01-14
 * License: CC0
 * Description: Given a rooted tree and a subset S of nodes, compute the minimal
 * subtree that contains all the nodes by adding vr(at most $|S|-1$)
 * pairwise LCA's and compressing edges.
 * Returns a list of (par, orig\_index) representing a tree rooted at 0.
 * The root points to itself.
 * Time: $O(|S| \log |S|)$
 * Status: Tested at CodeForces
 */
#pragma once

#include "LCA.h"

typedef vector<pair<int, int>> vpi;
vpi compressTree(LCA& lca, const vll& subset) {
	static vll rev; rev.resize(len(lca.time));
	vll li = subset; auto& T = lca.time;
	auto cmp = [&](int a, int b) { return T[a] < T[b]; };
	sort(vr(li), cmp);
	int m = len(li)-1;
	fl(i, m) {
		int a = li[i], b = li[i+1];
		li.push_back(lca.lca(a, b));
	}
	sort(vr(li), cmp);
	li.erase(unique(vr(li)), li.end());
	fl(i, len(li)) rev[li[i]] = i;
	vpi ret = {pair<ll, ll>(0, li[0])};
	fl(i, len(li)-1) {
		int a = li[i], b = li[i+1];
		ret.emplace_back(rev[lca.lca(a, b)], b);
	}
	return ret;
}
