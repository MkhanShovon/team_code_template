/**
 * Author: Johan Sannemo
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Calculate power of two jumps in a tree,
 * to support fast upward jumps and LCAs.
 * Assumes the root node points to itself.
 * Time: construction $O(N \log N)$, queries $O(\log N)$
 * Status: Tested at Petrozavodsk, also stress-tested via LCA.cpp
 */
#pragma once

vector<vll> treeJump(vll& P){
	int on = 1, d = 1;
	while(on < len(P)) on *= 2, d++;
	vector<vll> jmp(d, P);
	fls(i, 1, d - 1) fl(j, len(P))
		jmp[i][j] = jmp[i-1][jmp[i-1][j]];
	return jmp;
}

int jmp(vector<vll>& tbl, int nod, int steps){
	fl(i, len(tbl))
		if(steps&(1<<i)) nod = tbl[i][nod];
	return nod;
}

int lca(vector<vll>& tbl, vll& depth, int a, int b) {
	if (depth[a] < depth[b]) swap(a, b);
	a = jmp(tbl, a, depth[a] - depth[b]);
	if (a == b) return a;
	for (int i = len(tbl); i--;) {
		int c = tbl[i][a], d = tbl[i][b];
		if (c != d) a = c, b = d;
	}
	return tbl[0][a];
}
