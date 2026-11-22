/**
 * Author: Monjur Hossain Khan, OpenAI Codex
 * License: CC0
 * Description: Finds articulation points in an undirected graph.
 * Time: O(V + E)
 * Status: tested
 */
#pragma once

vll articulationPoints(const vector<vll>& g) {
	int n = len(g), T = 0;
	vll tin(n, -1), low(n), art(n);
	auto dfs = [&](int v, int p, auto&& dfs) -> void {
		tin[v] = low[v] = T++;
		int ch = 0;
		for (int to : g[v]) {
			if (to == p) continue;
			if (tin[to] != -1) low[v] = min(low[v], tin[to]);
			else {
				dfs(to, v, dfs);
				low[v] = min(low[v], low[to]);
				if (low[to] >= tin[v] && p != -1) art[v] = 1;
				ch++;
			}
		}
		if (p == -1 && ch > 1) art[v] = 1;
	};
	fl(i, n) if (tin[i] == -1) dfs(i, -1, dfs);
	return art;
}
