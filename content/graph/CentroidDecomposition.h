/**
 * Author: BUET_Orion
 * Date: 2026-11-22
 * License: CC0
 * Description: Centroid decomposition of a tree. par[c] is the parent of
 * c in the centroid tree (-1 for the root); its depth is $O(\log N)$.
 * To count/aggregate paths, process paths through centroid c at the marked
 * line, only visiting vertices with !rem[v].
 * Time: O(N \log N)
 * Status: tested
 */
#pragma once

struct Centroid {
	vector<vll> g; vll par, siz; vector<bool> rem;
	Centroid(const vector<vll>& g) : g(g), par(len(g), -1),
		siz(len(g)), rem(len(g)) { decomp(0, -1); }
	int calc(int v, int p) {
		siz[v] = 1;
		for (int u : g[v]) if (u != p && !rem[u]) siz[v] += calc(u, v);
		return siz[v];
	}
	int find(int v, int p, int tot) {
		for (int u : g[v]) if (u != p && !rem[u] && 2 * siz[u] > tot)
			return find(u, v, tot);
		return v;
	}
	void decomp(int v, int p) {
		int c = find(v, -1, calc(v, -1));
		par[c] = p; rem[c] = 1;
		// process all paths through c here
		for (int u : g[c]) if (!rem[u]) decomp(u, c);
	}
};
