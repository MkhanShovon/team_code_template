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
    
    // val == 1 (true node) maps to 2x
    // val == 0 (false node) maps to 2x + 1
    ll idx(ll x, ll val) { return 2 * x + !val; }
    
    // (u == u_val) OR (v == v_val)
    void either(ll u, ll u_val, ll v, ll v_val) { 
        g[idx(u, !u_val)].push_back(idx(v, v_val));
        g[idx(v, !v_val)].push_back(idx(u, u_val));
    }
    
    // (u == u_val) => (v == v_val)
    void implies(ll u, ll u_val, ll v, ll v_val) { 
        either(u, !u_val, v, v_val); 
    } 
    
    // (u == u_val) == (v == v_val)
    void equal(ll u, ll u_val, ll v, ll v_val) { 
        implies(u, u_val, v, v_val); 
        implies(v, v_val, u, u_val); 
    } 
    
    // (u == u_val) XOR (v == v_val)
    void xor_edge(ll u, ll u_val, ll v, ll v_val) { 
        either(u, u_val, v, v_val); 
        either(u, !u_val, v, !v_val); 
    } 
    
    // u MUST have the value u_val
    void force(ll u, ll u_val) { 
        either(u, u_val, u, u_val); 
    } 
    
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
 *     ts.either(0, 1, 1, 0);    // (0 is 1) OR (1 is 0) must be true
 *     ts.implies(1, 1, 2, 1);   // If (1 is 1), then (2 is 1)
 *     ts.xor_edge(0, 1, 2, 1);  // 0 and 2 must have opposite values
 *     ts.force(0, 0);           // 0 MUST be 0
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