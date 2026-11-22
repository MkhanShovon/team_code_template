/**
 * Author: chilli
 * License: CC0
 * Description: z[i] computes the length of the longest common prefix of s[i:] and s,
 * except z[0] = 0. (abacaba -> 0010301)
 * Time: O(n)
 * Status: stress-tested
 */
#pragma once

vll Z(const string& S) {
	vll z(len(S));
	int l = -1, r = -1;
	fls(i, 1, len(S) - 1) {
		z[i] = i >= r ? 0 : min(r - i, z[i - l]);
		while (i + z[i] < len(S) && S[i + z[i]] == S[z[i]])
			z[i]++;
		if (i + z[i] > r)
			l = i, r = i + z[i];
	}
	return z;
}
