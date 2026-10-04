/**
 * Author: Kosaraju Algorithm
 * Date: 2026-10-04
 * License: CC0
 * Description: Finds Strongly Connected Components (SCCs) in a directed graph.
 *  $comp[i]$ holds the SCC ID of node $i$ (topologically sorted).
 *  $G$ is the condensed DAG. $min\_edges()$ returns the minimum number 
 *  of edges to add to make the entire graph a single SCC.
 * Time: O(V + E)
 * Status: tested
 */
#pragma once

struct SCC {
    int n, scc_cnt = 0;
    vector<int> comp, vec;
    vector<vector<int>> G; // Condensed graph

	//nodes are 0-indexed
    SCC(const vector<vector<int>>& g) : n(g.size()), comp(n, -1) {
        vector<vector<int>> r(n);
        vector<bool> vis(n, 0);
        for (int u = 0; u < n; u++) for (int v : g[u]) r[v].push_back(u);
        
        auto dfs1 = [&](int u, auto& f) -> void {
            vis[u] = 1;
            for (int v : g[u]) if (!vis[v]) f(v, f);
            vec.push_back(u);
        };
        for (int i = 0; i < n; i++) if (!vis[i]) dfs1(i, dfs1);
        
        reverse(vec.begin(), vec.end());
        vis.assign(n, 0);
        
        auto dfs2 = [&](int u, auto& f) -> void {
            comp[u] = scc_cnt; vis[u] = 1;
            for (int v : r[u]) if (!vis[v]) f(v, f);
        };
        for (int u : vec) if (!vis[u]) dfs2(u, dfs2), scc_cnt++;
        
        G.resize(scc_cnt);
        for (int u = 0; u < n; u++) for (int v : g[u])
            if (comp[u] != comp[v]) G[comp[u]].push_back(comp[v]);
    }

    int min_edges() {
        if (scc_cnt <= 1) return 0;
        vector<int> in(scc_cnt), out(scc_cnt);
        for (int u = 0; u < scc_cnt; u++)
            for (int v : G[u]) in[v]++, out[u]++;
        
        int in_req = 0, out_req = 0;
        for (int i = 0; i < scc_cnt; i++) {
            in_req += !in[i];
            out_req += !out[i];
        }
        return max(in_req, out_req);
    }
};
//SCC graph(g);