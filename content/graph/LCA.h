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
	ll T = 0;
	vll time, path, ret, depth;
	RMQ<ll> rmq;
	LCA(vector<vll>& C) : time(len(C)), rmq((dfs(C,0,-1), ret)), depth(len(C)) {}
	void dfs(vector<vll>& C, ll v, ll par) {
		time[v] = T++;
		for (ll y : C[v]) if (y != par) {
			path.push_back(v), ret.push_back(time[v]);
            depth[y] = depth[v] + 1;
			dfs(C, y, v);
		}
	}

	ll lca(ll a, ll b) {
		if (a == b) return a;
		tie(a, b) = minmax(time[a], time[b]);
		return path[rmq.query(a, b)];
	}
	ll dist(ll a, ll b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};

int main() {
    // 1. Setup minimal tree (0-indexed, root is 0)
    // Edges: 0-1, 0-2, 2-3, 2-4
    ll N = 5; vector<vll> adj(N);
    adj[0]={1,2}; adj[1]={0}; adj[2]={0,3,4}; adj[3]={2}; adj[4]={2};

    // 2. Initialize LCA (O(N log N) prep)
    LCA tree(adj);

    // 3. O(1) Queries
    cout << tree.lca(1, 4) << "\n"; // Outputs 0 (LCA of 1 and 4)
    cout << tree.lca(3, 4) << "\n"; // Outputs 2 (LCA of 3 and 4)
    cout << tree.lca(2, 4) << "\n"; // Outputs 2 (LCA of an ancestor and its descendant)

    return 0;
}