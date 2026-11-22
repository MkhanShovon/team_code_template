/**
 * Author: BUET_Orion
 * Date: 2026-11-22
 * License: CC0
 * Description: res[i] = largest j < i with c(a[j], a[i]) (previous strictly
 * smaller for less<T>), or -1. Use greater<T> for previous greater,
 * less_equal / greater_equal for non-strict. For "next" versions, run on
 * the reversed array and map j to n-1-j (none = n).
 * Time: O(N)
 * Status: tested
 */
#pragma once

template<class T, class C = less<T>>
vll prevBetter(const vector<T>& a, C c = C()) {
	vll res(len(a), -1), st;
	fl(i, len(a)) {
		while (len(st) && !c(a[st.back()], a[i])) st.pop_back();
		if (len(st)) res[i] = st.back();
		st.push_back(i);
	}
	return res;
}
