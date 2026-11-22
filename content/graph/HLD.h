/**
 * Author: Benjamin Qi, Oleksandr Kulkov, chilli
 * Date: 2020-01-12
 * License: CC0
 * Source: https://codeforces.com/blog/entry/53170, https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
 * Description: Decomposes a tree into vertex disjoint heavy paths and light
 * edges such that the path from any leaf to the root contains at most log(n)
 * light edges. Code does additive modifications and max queries, but can
 * support commutative segtree modifications/queries on paths and subtrees.
 * Takes as input the full adjacency list. VALS\_EDGES being true means that
 * values are stored in the edges, as opposed to the nodes. All values
 * initialized to the segtree default. Root must be 0.
 * ST is any LazySeg; queryPath uses max (match identity -1e9 to iq).
 * Usage: auto cq=[](int a,int b){return max(a,b);};
 *  auto cu=[](int a,int b){return a+b;}; auto au=[](int a,int b,int){return a+b;};
 *  using ST = LazySeg<int,int,decltype(cq),decltype(cu),decltype(au)>;
 *  ST seg(N, -1e9, 0, cq, cu, au, vector<int>(N)); HLD<false, ST> hld(adj, \&seg);
 *  // pass a vector or leaves start at the identity -1e9
 * Time: O((\log N)^2)
 * Status: stress-tested against old HLD
 */
#pragma once

#include "../data-structures/LazySegmentTree.h"

template <bool VALS_EDGES, class ST> struct HLD {
    int N, tim = 0;
    vector<vll> adj;
    vll par, siz, rt, pos;
    ST *tree;

    HLD(vector<vll> adj_, ST* tree_)
        : N(len(adj_)), adj(adj_), par(N, -1), siz(N, 1),
          rt(N), pos(N), tree(tree_) { dfsSz(0); dfsHld(0); }
    void dfsSz(int v) {
        for (auto& u : adj[v]) {
            adj[u].erase(find(vr(adj[u]), v));
            par[u] = v;
            dfsSz(u);
            siz[v] += siz[u];
            if (siz[u] > siz[adj[v][0]]) swap(u, adj[v][0]);
        }
    }
    void dfsHld(int v) {
        pos[v] = tim++;
        for (int u : adj[v]) {
            rt[u] = (u == adj[v][0] ? rt[v] : u);
            dfsHld(u);
        }
    }
    template <class B> void process(int u, int v, B op) {
        for (;; v = par[rt[v]]) {
            if (pos[u] > pos[v]) swap(u, v);
            if (rt[u] == rt[v]) break;
            op(pos[rt[v]], pos[v] + 1);
        }
        op(pos[u] + VALS_EDGES, pos[v] + 1);
    }
    void modifyPath(int u, int v, int val) {
        process(u, v, [&](int l, int r) { tree->upd(l, r, val); });
    }
    int queryPath(int u, int v) { 
        int res = -1e9; // Must match Identity Query (iq) of Segment Tree
        process(u, v, [&](int l, int r) { res = max(res, tree->qry(l, r)); });
        return res;
    }
    int querySubtree(int v) { 
        return tree->qry(pos[v] + VALS_EDGES, pos[v] + siz[v]);
    }
};
