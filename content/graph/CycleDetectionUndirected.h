/**
 * Author: Unknown
 * Date: 2024-01-01
 * License: CC0
 * Source: own work
 * Description: Cycle detection and reconstruction in an undirected graph.
 * Time: O(V + E)
 * Status: tested
 */
#pragma once

struct UndirectedCycle {
	int n;
	vector<vector<int>> adj;
	vector<bool> visited;
	vector<int> parent;
	int cycle_start = -1, cycle_end = -1;

	UndirectedCycle(int n) : n(n), adj(n), visited(n, false), parent(n, -1) {}

	bool dfs(int v, int par) {
		visited[v] = true;
		for (int u : adj[v]) {
			if (u == par) continue;
			if (visited[u]) {
				cycle_end = v;
				cycle_start = u;
				return true;
			}
			parent[u] = v;
			if (dfs(u, parent[u])) return true;
		}
		return false;
	}

	vector<int> find_cycle() {
		for (int v = 0; v < n; v++) {
			if (!visited[v] && dfs(v, parent[v])) break;
		}
		if (cycle_start == -1) return {};
		vector<int> cycle;
		cycle.push_back(cycle_start);
		for (int v = cycle_end; v != cycle_start; v = parent[v])
			cycle.push_back(v);
		cycle.push_back(cycle_start);
		return cycle;
	}
};
