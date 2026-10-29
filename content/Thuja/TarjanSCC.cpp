class TarjanSCC {
    int n;
    vector<vector<int>> adj;
    vector<int> disc, low;
    vector<bool> on_stack;
    stack<int> st;
    int timer;
    
    void dfs(int u, vector<int>& comp_id, vector<vector<int>>& sccs, int& scc_count) {
        disc[u] = low[u] = ++timer;
        st.push(u);
        on_stack[u] = true;

        for (int v : adj[u]) {
            if (disc[v] == -1) {
                dfs(v, comp_id, sccs, scc_count);
                low[u] = min(low[u], low[v]);
            } else if (on_stack[v]) {
                low[u] = min(low[u], disc[v]);
            }
        }

        // If u is the root of the SCC
        if (low[u] == disc[u]) {
            vector<int> current_scc;
            while (true) {
                int v = st.top();
                st.pop();
                on_stack[v] = false;
                comp_id[v] = scc_count;
                current_scc.push_back(v);
                if (u == v) break;
            }
            sccs.push_back(current_scc);
            scc_count++;
        }
    }

public:
    TarjanSCC(int n, const vector<vector<int>>& adj) : n(n), adj(adj) {
        disc.assign(n, -1);
        low.assign(n, -1);
        on_stack.assign(n, false);
        timer = 0;
    }

    // Returns a pair: {total_scc_count, list_of_all_sccs}
    // and populates comp_id[u] with the SCC ID for each vertex u.
    pair<int, vector<vector<int>>> find_sccs(vector<int>& comp_id) {
        comp_id.assign(n, -1);
        vector<vector<int>> sccs;
        int scc_count = 0;

        for (int i = 0; i < n; i++) {
            if (disc[i] == -1) {
                dfs(i, comp_id, sccs, scc_count);
            }
        }
        return {scc_count, sccs};
    }
};
