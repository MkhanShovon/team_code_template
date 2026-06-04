/**
 * Author: Unknown
 * Date: 2024-01-01
 * License: CC0
 * Source: own work
 * Description: Euler tour technique on trees. Flattens a tree into an array where each subtree corresponds to a contiguous range.
 * Time: O(N)
 * Status: tested
 */
#pragma once

int tim = 0;
vector<int> start_time, finish_time, v;
vector<vector<int>> adj;

void dfs_euler(int node, int p = -1) {
    start_time[node] = ++tim;
    for (auto u : adj[node]) {
        if (u == p) continue;
        dfs_euler(u, node);
    }
    finish_time[node] = tim;
}
