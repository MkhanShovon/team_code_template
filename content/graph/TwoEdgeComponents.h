/**
 * Author: Monjur Hossain Khan, OpenAI Codex
 * License: CC0
 * Description: Two-edge-connected components and bridge tree of an undirected
 * graph. Supports parallel edges.
 * Time: O(V + E)
 * Status: tested
 */
#pragma once

struct TwoEdgeCC {
	int n, comps = 0;
	vector<vi> g, tree;
	vi comp, ord, low, used;
	vector<pii> bridges;
	TwoEdgeCC(const vector<vi>& gr) : n(sz(gr)), g(gr), comp(n, -1),
		ord(n), low(n), used(n) {
		int t = 0;
		rep(i,0,n) if (!used[i]) dfs(i, -1, t), dfs2(i, comps++);
		buildTree();
	}
	void dfs(int v, int p, int& t) {
		used[v] = 1; ord[v] = low[v] = t++;
		bool skippedParent = false;
		for (int to : g[v]) {
			if (to == p && !skippedParent) { skippedParent = true; continue; }
			if (used[to]) low[v] = min(low[v], ord[to]);
			else dfs(to, v, t), low[v] = min(low[v], low[to]);
		}
	}
	void dfs2(int v, int c) {
		comp[v] = c;
		for (int to : g[v]) if (comp[to] == -1) {
			if (ord[v] < low[to]) bridges.push_back({v, to}), dfs2(to, comps++);
			else dfs2(to, c);
		}
	}
	void buildTree() {
		tree.assign(comps, {});
		for (auto [a, b] : bridges) {
			a = comp[a], b = comp[b];
			tree[a].push_back(b); tree[b].push_back(a);
		}
	}
};
