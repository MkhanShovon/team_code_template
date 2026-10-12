/**
 * Author: Modified KACTL
 * Date: 2026-10-12
 * License: CC0
 * Description: 0-indexed 2-SAT solver. Reuses SCC template to save space.
 *  Uses KACTL's ~x trick to represent NOT x. 
 *  Variables are 0 to n-1. After calling ok(), ans[i] holds the truth value.
 * Time: O(V + E)
 * Status: tested
 */
#pragma once

// Requires SCC struct defined above

struct TwoSat {
    ll n; 
    vector<vector<ll>> g; 
    vector<ll> ans;
    
    TwoSat(ll n) : n(n), g(2 * n) {}
    
    // Maps x to 2x (true node) and ~x to 2x+1 (false node)
    ll idx(ll x) { return x < 0 ? 2 * ~x + 1 : 2 * x; }
    
    void either(ll u, ll v) { // u OR v
        g[idx(~u)].push_back(idx(v));
        g[idx(~v)].push_back(idx(u));
    }
    void implies(ll u, ll v) { either(~u, v); } // u => v
    void equal(ll u, ll v) { implies(u, v); implies(v, u); } // u == v
    void xor_edge(ll u, ll v) { either(u, v); either(~u, ~v); } // u ^ v = 1
    void force(ll u) { either(u, u); } // u must be true (pass ~u for false)
    
    bool ok() {
        SCC scc(g);
        ans.assign(n, 0);
        for (ll i = 0; i < n; i++) {
            if (scc.comp[2 * i] == scc.comp[2 * i + 1]) return 0;
            // Kosaraju: comp ID decreases along topological sort.
            ans[i] = scc.comp[2 * i] > scc.comp[2 * i + 1]; 
        }
        return 1;
    }
};

/*
 * Usage Example:
 * 
 * int main() {
 *     ll n = 3; // 3 variables: 0, 1, 2
 *     TwoSat ts(n);
 *     
 *     ts.either(0, ~1);      // 0 OR (NOT 1) must be true
 *     ts.implies(1, 2);      // If 1 is true, 2 must be true
 *     ts.xor_edge(0, 2);     // 0 and 2 must have different truth values
 *     ts.force(~0);          // 0 MUST be false
 *     
 *     if (!ts.ok()) {
 *         cout << "Impossible\n";
 *     } else {
 *         cout << "Possible\n";
 *         for (ll i = 0; i < n; i++) {
 *             cout << "Var " << i << " = " << ts.ans[i] << '\n';
 *         }
 *     }
 * }
 */