/**
 * Author: Simon Lindholm
 * Date: 2016-09-06
 * License: CC0
 * Source: folklore
 * Description: Calculates determinant of a matrix. Destroys the matrix.
 * Time: $O(N^3)$
 * Status: somewhat tested
 */
#pragma once

double det(vector<vector<double>>& a) {
	int n = len(a); double res = 1;
	fl(i, n) {
		int b = i;
		fls(j, i+1, n - 1) if (fabs(a[j][i]) > fabs(a[b][i])) b = j;
		if (i != b) swap(a[i], a[b]), res *= -1;
		res *= a[i][i];
		if (res == 0) return 0;
		fls(j, i+1, n - 1) {
			double v = a[j][i] / a[i][i];
			if (v != 0) fls(k, i+1, n - 1) a[j][k] -= v * a[i][k];
		}
	}
	return res;
}
