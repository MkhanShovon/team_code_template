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
 * Time: O((\log N)^2)
 * Status: stress-tested against old HLD
 */
#pragma once

#include "../data-structures/LazySegmentTree.h"

template <bool VALS_EDGES, class ST> struct HLD {
    int N, tim = 0;
    vector<vi> adj;
    vi par, siz, rt, pos;
    ST *tree; // generic pointer to your LazySeg

    HLD(vector<vi> adj_, ST* tree_)
        : N(sz(adj_)), adj(adj_), par(N, -1), siz(N, 1),
          rt(N), pos(N), tree(tree_) { dfsSz(0); dfsHld(0); }
          
    void dfsSz(int v) {
        for (int& u : adj[v]) {
            adj[u].erase(find(all(adj[u]), v));
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
        // Updated to use ->upd
        process(u, v, [&](int l, int r) { tree->upd(l, r, val); });
    }
    int queryPath(int u, int v) { 
        int res = -1e9; // Must match Identity Query (iq) of Segment Tree
        // Updated to use ->qry
        process(u, v, [&](int l, int r) {
                res = max(res, tree->qry(l, r));
        });
        return res;
    }
    int querySubtree(int v) { 
        // Updated to use ->qry
        return tree->qry(pos[v] + VALS_EDGES, pos[v] + siz[v]);
    }
};

// ==========================================
// 3. MINIMAL USAGE EXAMPLE
// ==========================================
int main() {
    int N = 5;
    
    // 1. Build the undirected adjacency list
    vector<vi> adj(N);
    adj[0] = {1, 2}; adj[1] = {0, 3, 4}; adj[2] = {0}; 
    adj[3] = {1}; adj[4] = {1};

    // 2. Define operations for a RANGE ADD / RANGE MAX Segment Tree
    // (We use Max because HLD's queryPath function hardcodes `max()`)
    auto cq_max = [](int a, int b) { return max(a, b); };
    auto cu_add = [](int a, int b) { return a + b; };
    auto au_max = [](int a, int b, int len) { return a + b; };
    
    // 3. Define the precise Type of the Segment Tree based on the lambdas
    using SegType = LazySeg<int, int, decltype(cq_max), decltype(cu_add), decltype(au_max)>;
    
    // 4. Instantiate the Segment Tree
    // Init sizes, Identifiers (-1e9 for Max Query, 0 for Add Update), and lambdas
    SegType seg(N, -1e9, 0, cq_max, cu_add, au_max);

    // 5. Instantiate HLD, passing the pointer to our Segment Tree
    HLD<false, SegType> hld(adj, &seg);

    // 6. Test Operations
    hld.modifyPath(3, 4, 10); // Path 3 -> 1 -> 4
    cout << "Max on path 0 to 4: " << hld.queryPath(0, 4) << "\n"; // Outputs 10
    
    hld.modifyPath(0, 0, 5);  // Add 5 to node 0
    cout << "Max in subtree 2: " << hld.querySubtree(2) << "\n";   // Outputs 0
    cout << "Max in whole tree: " << hld.querySubtree(0) << "\n";  // Outputs 10

    return 0;
}