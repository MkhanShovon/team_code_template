/**
 * Author: Unknown
 * Date: 2024-01-01
 * License: CC0
 * Source: own work
 * Description: Counts the number of inversions in an array using an
 *   order-statistic tree. An inversion is a pair (i, j) with i < j
 *   and a[i] > a[j].
 * Time: O(N \log N)
 * Status: tested
 */
#pragma once

#include <bits/extc++.h> /** keep-include */
using namespace __gnu_pbds;

template <class T>
using Tree =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// Returns number of inversions in array a (all elements must be distinct).
// For duplicates, compress to unique indices first.
ll inversions(vector<int>& a) {
	Tree<int> t;
	ll inv = 0;
	for (int i = 0; i < (int)a.size(); i++) {
		inv += i - t.order_of_key(a[i]);
		t.insert(a[i]);
	}

	//t.order_of_key(x) returns the number of elements in the tree that are strictly less than x.
	//*t.find_by_order(k) returns an iterator to the k-th smallest element in the tree (0-indexed).
	return inv;
}
