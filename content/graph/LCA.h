/**
 * Author: chilli, pajenegod
 * Date: 2020-02-20
 * License: CC0
 * Source: Folklore
 * Description: Data structure for computing lowest common ancestors in a tree
 * (with 0 as root). C should be an adjacency list of the tree, either directed
 * or undirected.
 * Time: $O(N \log N + Q)$
 * Status: stress-tested
 */
#pragma once

#include "../data-structures/RMQ.h"

struct LCA {
	int T = 0;
	vi time, path, ret;
	RMQ<int> rmq;

	LCA(vector<vi>& C) : time(sz(C)), rmq((dfs(C,0,-1), ret)) {}
	void dfs(vector<vi>& C, int v, int par) {
		time[v] = T++;
		for (int y : C[v]) if (y != par) {
			path.push_back(v), ret.push_back(time[v]);
			dfs(C, y, v);
		}
	}

	int lca(int a, int b) {
		if (a == b) return a;
		tie(a, b) = minmax(time[a], time[b]);
		return path[rmq.query(a, b)];
	}
	//dist(a,b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};

int main() {
    // 1. Setup minimal tree (0-indexed, root is 0)
    // Edges: 0-1, 0-2, 2-3, 2-4
    int N = 5; vector<vi> adj(N);
    adj[0]={1,2}; adj[1]={0}; adj[2]={0,3,4}; adj[3]={2}; adj[4]={2};

    // 2. Initialize LCA (O(N log N) prep)
    LCA tree(adj);

    // 3. O(1) Queries
    cout << tree.lca(1, 4) << "\n"; // Outputs 0 (LCA of 1 and 4)
    cout << tree.lca(3, 4) << "\n"; // Outputs 2 (LCA of 3 and 4)
    cout << tree.lca(2, 4) << "\n"; // Outputs 2 (LCA of an ancestor and its descendant)

    return 0;
}