class BridgeFinder {
    void dfs(int u, int p, vector<vector<int>>& adj, vector<int>& tin, vector<int>& low, int& timer, vector<pair<int, int>>& bridges) {
        tin[u] = low[u] = timer++;
        for (int v : adj[u]) {
            if (v == p) continue;
            if (tin[v] != -1) {
                // Back-edge
                low[u] = min(low[u], tin[v]);
            } else {
                // Forward-edge
                dfs(v, u, adj, tin, low, timer, bridges);
                low[u] = min(low[u], low[v]);
                
                // Bridge condition
                if (low[v] > tin[u]) {
                    bridges.push_back({min(u, v), max(u, v)});
                }
            }
        }
    }

public:
    vector<pair<int, int>> findBridges(int n, vector<pair<int, int>>& edges) {
        vector<vector<int>> adj(n);
        for (auto& edge : edges) {
            adj[edge.first].push_back(edge.second);
            adj[edge.second].push_back(edge.first);
        }
        
        vector<int> tin(n, -1);
        vector<int> low(n, -1);
        int timer = 0;
        vector<pair<int, int>> bridges;
        
        for (int i = 0; i < n; i++) {
            if (tin[i] == -1) {
                dfs(i, -1, adj, tin, low, timer, bridges);
            }
        }
        return bridges;
    }
};
