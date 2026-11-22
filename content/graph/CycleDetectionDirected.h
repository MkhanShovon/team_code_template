/**
 * Author: BUET_Orion
 * Date: 2026-11-22
 * License: CC0
 * Description: Finds a cycle in a directed graph; returns its vertices in
 * order (first vertex not repeated), or empty if the graph is a DAG.
 * For undirected graphs: skip the edge to the parent once, and use
 * vis $\neq$ 0 instead of vis == 1 (or just use UnionFind).
 * Time: O(V + E)
 * Status: tested
 */
#pragma once

vll findCycle(const vector<vll>& g) {
	int n = len(g); vll vis(n), par(n, -1), cyc;
	auto dfs = [&](auto&& self, int v) -> bool {
		vis[v] = 1;
		for (int u : g[v]) {
			if (vis[u] == 1) {
				for (int x = v; x != u; x = par[x]) cyc.push_back(x);
				cyc.push_back(u); reverse(vr(cyc)); return 1;
			}
			if (!vis[u] && (par[u] = v, self(self, u))) return 1;
		}
		vis[v] = 2; return 0;
	};
	fl(i, n) if (!vis[i] && dfs(dfs, i)) break;
	return cyc;
}
