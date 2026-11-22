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
	LCA(vector<vll>& C) : time(len(C)), depth(len(C)), rmq((dfs(C,0,-1), ret)) {}
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
