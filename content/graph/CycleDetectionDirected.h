/**
 * Author: Unknown
 * Date: 2024-01-01
 * License: CC0
 * Source: own work
 * Description: Cycle detection and reconstruction in a directed graph.
 * Time: O(V + E)
 * Status: tested
 */
#pragma once

struct DirectedCycle {
	int n;
	vector<vector<int>> adj;
	vector<char> color;
	vector<int> parent;
	int cycle_start = -1, cycle_end = -1;

	DirectedCycle(int n) : n(n), adj(n), color(n, 0), parent(n, -1) {}

	bool dfs(int v) {
		color[v] = 1;
		for (int u : adj[v]) {
			if (color[u] == 0) {
				parent[u] = v;
				if (dfs(u)) return true;
			} else if (color[u] == 1) {
				cycle_end = v;
				cycle_start = u;
				return true;
			}
		}
		color[v] = 2;
		return false;
	}

	vector<int> find_cycle() {
		for (int v = 0; v < n; v++) {
			if (color[v] == 0 && dfs(v)) break;
		}
		if (cycle_start == -1) return {};
		vector<int> cycle;
		cycle.push_back(cycle_start);
		for (int v = cycle_end; v != cycle_start; v = parent[v])
			cycle.push_back(v);
		cycle.push_back(cycle_start);
		reverse(all(cycle));
		return cycle;
	}
};
