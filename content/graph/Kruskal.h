/**
 * Author: Unknown
 * Date: 2024-01-01
 * License: CC0
 * Source: own work
 * Description: Kruskal's algorithm for finding the minimum spanning tree of a graph.
 * Time: O(E \log E)
 * Status: tested
 */
#pragma once

#include "../data-structures/UnionFind.h"

struct Edge {
	ll w; int u, v;
	bool operator<(const Edge& o) const { return w < o.w; }
};

ll kruskal(int n, vector<Edge>& e) {
	UF uf(n); // 0-based indexing
	sort(all(e));
	ll ans = 0;
	int edges = 0;
	for (auto [w, u, v] : e) {
		if (uf.join(u, v)) {
			ans += w;
			edges++;
		}
	}
	return edges == n - 1 ? ans : -1;
}
