/**
 * Author: BUET_Orion
 * Date: 2026-11-22
 * License: CC0
 * Description: Replaces each value by its rank among distinct values
 * (0-indexed). Returns the sorted distinct values (vals[a[i]] = old a[i]).
 * Time: O(N \log N)
 * Status: tested
 */
#pragma once

template<class T> vector<T> compress(vector<T>& a) {
	vector<T> v = a;
	sort(vr(v)), v.erase(unique(vr(v)), v.end());
	for (T& x : a) x = lower_bound(vr(v), x) - v.begin();
	return v;
}
