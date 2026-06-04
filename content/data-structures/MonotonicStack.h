/**
 * Author: Monjur Hossain Khan, OpenAI Codex
 * License: CC0
 * Description: Previous/next smaller/greater indices using a monotonic stack.
 * Strict variants use < or >; pass false for smaller-or-equal / greater-or-equal barriers.
 * Time: O(N)
 * Status: tested
 */
#pragma once

template<class T>
vi nextSmaller(const vector<T>& a, bool strict = true) {
	vi res(sz(a), sz(a)), st;
	rep(i,0,sz(a)) {
		while (!st.empty() && (strict ? a[i] < a[st.back()] : a[i] <= a[st.back()]))
			res[st.back()] = i, st.pop_back();
		st.push_back(i);
	}
	return res;
}
template<class T>
vi prevSmaller(const vector<T>& a, bool strict = true) {
	vi res(sz(a), -1), st;
	rep(i,0,sz(a)) {
		while (!st.empty() && (strict ? a[i] <= a[st.back()] : a[i] < a[st.back()]))
			st.pop_back();
		if (!st.empty()) res[i] = st.back();
		st.push_back(i);
	}
	return res;
}
template<class T>
vi nextGreater(const vector<T>& a, bool strict = true) {
	vi res(sz(a), sz(a)), st;
	rep(i,0,sz(a)) {
		while (!st.empty() && (strict ? a[i] > a[st.back()] : a[i] >= a[st.back()]))
			res[st.back()] = i, st.pop_back();
		st.push_back(i);
	}
	return res;
}
template<class T>
vi prevGreater(const vector<T>& a, bool strict = true) {
	vi res(sz(a), -1), st;
	rep(i,0,sz(a)) {
		while (!st.empty() && (strict ? a[i] >= a[st.back()] : a[i] > a[st.back()]))
			st.pop_back();
		if (!st.empty()) res[i] = st.back();
		st.push_back(i);
	}
	return res;
}
