#include <bits/stdc++.h>
using namespace std;

class BridgeBlockTree {
private:
    int n, m;
    vector<pair<int, int>> edges;
    vector<vector<int>> adj;
    vector<int> tin, low;
    int timer;
    set<pair<int, int>> bridge_set;
    vector<int> comp;
    int comp_count;
    vector<vector<int>> condensed_tree;

    void dfs_bridge(int u, int p) {
        tin[u] = low[u] = timer++;
        for (int v : adj[u]) {
            if (v == p) continue;
            if (tin[v] != -1) {
                low[u] = min(low[u], tin[v]);
            } else {
                dfs_bridge(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] > tin[u]) {
                    bridge_set.insert({min(u, v), max(u, v)});
                }
            }
        }
    }

    void dfs_comp(int u, int cid) {
        comp[u] = cid;
        for (int v : adj[u]) {
            if (comp[v] == -1) {
                // Do not cross bridges within the same component
                if (bridge_set.count({min(u, v), max(u, v)})) continue;
                dfs_comp(v, cid);
            }
        }
    }

public:
    BridgeBlockTree(int n, const vector<pair<int, int>>& edges) : n(n), edges(edges) {
        m = edges.size();
        adj.resize(n);
        for (auto& edge : edges) {
            adj[edge.first].push_back(edge.second);
            adj[edge.second].push_back(edge.first);
        }
        
        tin.assign(n, -1);
        low.assign(n, -1);
        timer = 0;
        
        // Step 1: Find all bridges
        for (int i = 0; i < n; i++) {
            if (tin[i] == -1) {
                dfs_bridge(i, -1);
            }
        }
        
        // Step 2: Assign unique component IDs
        comp.assign(n, -1);
        comp_count = 0;
        for (int i = 0; i < n; i++) {
            if (comp[i] == -1) {
                dfs_comp(i, comp_count++);
            }
        }
        
        // Step 3: Build the condensation tree
        condensed_tree.resize(comp_count);
        map<pair<int, int>, int> done;
        for (auto& edge : edges) {
            int u = comp[edge.first];
            int v = comp[edge.second];
            if (u != v && !done[{u, v}]) {
                condensed_tree[u].push_back(v);
                condensed_tree[v].push_back(u);
                done[{u, v}] = done[{v, u}] = 1;
            }
        }
    }

    // Returns the number of 2-edge-connected components (nodes in the condensed tree)
    int get_component_count() const {
        return comp_count;
    }

    // Returns the mapping of original node -> component ID
    const vector<int>& get_components() const {
        return comp;
    }

    // Returns the adjacency list of the condensed tree
    const vector<vector<int>>& get_condensed_tree() const {
        return condensed_tree;
    }

    // Returns the set of bridges as pairs of original node indices
    const set<pair<int, int>>& get_bridges() const {
        return bridge_set;
    }
};
