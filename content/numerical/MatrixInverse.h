/**
 * Author: Max Bennedich
 * Date: 2004-02-08
 * Description: Invert matrix $A$. Returns rank; result is stored in $A$ unless singular (rank < n).
 * Can easily be extended to prime moduli; for prime powers, repeatedly
 * set $A^{-1} = A^{-1} (2I - AA^{-1})\  (\text{mod }p^k)$ where $A^{-1}$ starts as
 * the inverse of A mod p, and k is doubled in each step.
 * Time: O(n^3)
 * Status: Slightly tested
 */
#pragma once

int matInv(vector<vector<double>>& A) {
	int n = len(A); vll col(n);
	vector<vector<double>> tmp(n, vector<double>(n));
	fl(i, n) tmp[i][i] = 1, col[i] = i;

	fl(i, n) {
		int r = i, c = i;
		fls(j, i, n - 1) fls(k, i, n - 1)
			if (fabs(A[j][k]) > fabs(A[r][c]))
				r = j, c = k;
		if (fabs(A[r][c]) < 1e-12) return i;
		A[i].swap(A[r]); tmp[i].swap(tmp[r]);
		fl(j, n)
			swap(A[j][i], A[j][c]), swap(tmp[j][i], tmp[j][c]);
		swap(col[i], col[c]);
		double v = A[i][i];
		fls(j, i+1, n - 1) {
			double f = A[j][i] / v;
			A[j][i] = 0;
			fls(k, i+1, n - 1) A[j][k] -= f*A[i][k];
			fl(k, n) tmp[j][k] -= f*tmp[i][k];
		}
		fls(j, i+1, n - 1) A[i][j] /= v;
		fl(j, n) tmp[i][j] /= v;
		A[i][i] = 1;
	}

	/// forget A at this point, just eliminate tmp backward
	for (int i = n-1; i > 0; --i) fl(j, i) {
		double v = A[j][i];
		fl(k, n) tmp[j][k] -= v*tmp[i][k];
	}

	fl(i, n) fl(j, n) A[col[i]][col[j]] = tmp[i][j];
	return n;
}
