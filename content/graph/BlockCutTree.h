/**
 * Author: Monjur Hossain Khan, OpenAI Codex
 * License: CC0
 * Description: Builds the block-cut forest of an undirected graph. Component
 * nodes come first; articulation-point nodes follow. id[v] maps each original
 * vertex to its node in the block-cut forest.
 * Time: O(V + E)
 * Status: tested
 */
#pragma once

struct BlockCutTree {
	vector<vll> comps, tree, g;
	vll tin, low, isArt, id, st;
	int T = 0;
	BlockCutTree(const vector<vll>& gr) : g(gr), tin(len(g), -1), low(len(g)),
		isArt(len(g)), id(len(g), -1) {
		fl(i, len(g)) if (tin[i] == -1) st.clear(), dfs(i, -1);
		build();
	}
	void dfs(int v, int p) {
		tin[v] = low[v] = T++;
		st.push_back(v);
		int ch = 0;
		for (int to : g[v]) {
			if (to == p) continue;
			if (tin[to] != -1) low[v] = min(low[v], tin[to]);
			else {
				ch++; dfs(to, v); low[v] = min(low[v], low[to]);
				if (low[to] >= tin[v]) {
					if (p != -1 || ch > 1) isArt[v] = 1;
					comps.push_back({v});
					while (comps.back().back() != to)
						comps.back().push_back(st.back()), st.pop_back();
				}
			}
		}
		if (p == -1 && !ch) comps.push_back({v});
	}
	void build() {
		int c = len(comps);
		fl(v, len(g)) if (isArt[v]) id[v] = c++;
		tree.assign(c, {});
		fl(i, len(comps)) for (int v : comps[i]) {
			if (isArt[v]) tree[i].push_back(id[v]), tree[id[v]].push_back(i);
			else id[v] = i;
		}
	}
};
