/**
 * Author: Per Austrin, Simon Lindholm
 * Date: 2004-02-08
 * License: CC0
 * Description: Solves $A * x = b$. If there are multiple solutions, an arbitrary one is returned.
 *  Returns rank, or -1 if no solutions. Data in $A$ and $b$ is lost.
 * Time: O(n^2 m)
 * Status: tested on kattis:equationsolver, and bruteforce-tested mod 3 and 5 for n,m <= 3
 */
#pragma once

typedef vector<double> vd;
const double eps = 1e-12;

int solveLinear(vector<vd>& A, vd& b, vd& x) {
	int n = len(A), m = len(x), rank = 0, br, bc;
	if (n) assert(len(A[0]) == m);
	vll col(m); iota(vr(col), 0);

	fl(i, n) {
		double v, bv = 0;
		fls(r, i, n - 1) fls(c, i, m - 1)
			if ((v = fabs(A[r][c])) > bv)
				br = r, bc = c, bv = v;
		if (bv <= eps) {
			fls(j, i, n - 1) if (fabs(b[j]) > eps) return -1;
			break;
		}
		swap(A[i], A[br]);
		swap(b[i], b[br]);
		swap(col[i], col[bc]);
		fl(j, n) swap(A[j][i], A[j][bc]);
		bv = 1/A[i][i];
		fls(j, i+1, n - 1) {
			double fac = A[j][i] * bv;
			b[j] -= fac * b[i];
			fls(k, i+1, m - 1) A[j][k] -= fac*A[i][k];
		}
		rank++;
	}

	x.assign(m, 0);
	for (int i = rank; i--;) {
		b[i] /= A[i][i];
		x[col[i]] = b[i];
		fl(j, i) b[j] -= A[j][i] * b[i];
	}
	return rank; // (multiple solutions if rank < m)
}
