/**
 * Author: Johan Sannemo
 * Date: 2016-12-15
 * License: CC0
 * Description: pi[x] computes the length of the longest prefix of s that ends at x,
 * other than s[0...x] itself (abacaba -> 0010123).
 * Can be used to find all occurrences of a string.
 * Time: O(n)
 * Status: Tested on kattis:stringmatching
 */
#pragma once

vll pi(const string& s) {
	vll p(len(s));
	fls(i, 1, len(s) - 1) {
		int g = p[i-1];
		while (g && s[i] != s[g]) g = p[g-1];
		p[i] = g + (s[i] == s[g]);
	}
	return p;
}

vll match(const string& s, const string& pat) {
	vll p = pi(pat + '\0' + s), res;
	fls(i, len(p)-len(s), len(p) - 1)
		if (p[i] == len(pat)) res.push_back(i - 2 * len(pat));
	return res;
}
