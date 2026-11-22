/**
 * Author: Simon Lindholm
 * Date: 2016-12-08
 * Source: The regular matrix inverse code
 * Description: Invert matrix $A$ modulo a prime.
 * Returns rank; result is stored in $A$ unless singular (rank < n).
 * For prime powers, repeatedly set $A^{-1} = A^{-1} (2I - AA^{-1})\  (\text{mod }p^k)$ where $A^{-1}$ starts as
 * the inverse of A mod p, and k is doubled in each step.
 * Time: O(n^3)
 * Status: Slightly tested
 */
#pragma once

#include "../number-theory/ModPow.h"

int matInv(vector<vector<ll>>& A) {
	int n = len(A); vll col(n);
	vector<vector<ll>> tmp(n, vector<ll>(n));
	fl(i, n) tmp[i][i] = 1, col[i] = i;

	fl(i, n) {
		int r = i, c = i;
		fls(j, i, n - 1) fls(k, i, n - 1) if (A[j][k]) {
			r = j; c = k; goto found;
		}
		return i;
found:
		A[i].swap(A[r]); tmp[i].swap(tmp[r]);
		fl(j, n)
			swap(A[j][i], A[j][c]), swap(tmp[j][i], tmp[j][c]);
		swap(col[i], col[c]);
		ll v = modpow(A[i][i], mod - 2);
		fls(j, i+1, n - 1) {
			ll f = A[j][i] * v % mod;
			A[j][i] = 0;
			fls(k, i+1, n - 1) A[j][k] = (A[j][k] - f*A[i][k]) % mod;
			fl(k, n) tmp[j][k] = (tmp[j][k] - f*tmp[i][k]) % mod;
		}
		fls(j, i+1, n - 1) A[i][j] = A[i][j] * v % mod;
		fl(j, n) tmp[i][j] = tmp[i][j] * v % mod;
		A[i][i] = 1;
	}

	for (int i = n-1; i > 0; --i) fl(j, i) {
		ll v = A[j][i];
		fl(k, n) tmp[j][k] = (tmp[j][k] - v*tmp[i][k]) % mod;
	}

	fl(i, n) fl(j, n)
		A[col[i]][col[j]] = tmp[i][j] % mod + (tmp[i][j] < 0)*mod;
	return n;
}
