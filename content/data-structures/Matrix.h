/**
 * Author: Ulf Lundstrom
 * Date: 2009-08-03
 * License: CC0
 * Source: My head
 * Description: Basic operations on square matrices.
 * Usage: Matrix<int, 3> A;
 *  A.d = {{{{1,2,3}}, {{4,5,6}}, {{7,8,9}}}};
 *  array<int, 3> vec = {1,2,3};
 *  vec = (A^N) * vec;
 * Status: tested
 */
#pragma once

template<class T, int N> struct Matrix {
	typedef Matrix M;
	array<array<T, N>, N> d{};
	Matrix() = default;
	Matrix(vector<vector<T>> v) {
		fls(i,0,N - 1) fls(j,0,N - 1) d[i][j] = v[i][j];
	}
	M operator*(const M& m) const {
		M a;
		fls(i,0,N - 1) fls(j,0,N - 1)
			fls(k,0,N - 1) a.d[i][k] += d[i][j] * m.d[j][k];
		return a;
	}
	array<T, N> operator*(const array<T, N>& vec) const {
		array<T, N> ret{};
		fls(i,0,N - 1) fls(j,0,N - 1) ret[i] += d[i][j] * vec[j];
		return ret;
	}
	M operator^(ll p) const {
		assert(p >= 0);
		M a, b(*this);
		fls(i,0,N - 1) a.d[i][i] = 1;
		while (p) {
			if (p&1) a = a*b;
			b = b*b;
			p >>= 1;
		}
		return a;
	}
};

const double EPS = 1e-9;
// Returns 0: no sol, 1: unique, 2: infinite sol. Matrix 'a' is n x (m + 1)
int gauss(vector<vector<double>>& a, vector<double>& ans) {
    int n = a.size(), m = a[0].size() - 1;
    vector<int> w(m, -1);
    for (int c = 0, r = 0; c < m && r < n; ++c) {
        int sel = r;
        for (int i = r; i < n; ++i) if (abs(a[i][c]) > abs(a[sel][c])) sel = i;
        if (abs(a[sel][c]) < EPS) continue;
        for (int i = c; i <= m; ++i) swap(a[sel][i], a[r][i]);
        w[c] = r;
        for (int i = 0; i < n; ++i) if (i != r) {
            double k = a[i][c] / a[r][c];
            for (int j = c; j <= m; ++j) a[i][j] -= a[r][j] * k;
        }
        ++r;
    }
    ans.assign(m, 0);
    for (int i = 0; i < m; ++i) if (w[i] != -1) ans[i] = a[w[i]][m] / a[w[i]][i];
    for (int i = 0; i < n; ++i) {
        double sum = 0;
        for (int j = 0; j < m; ++j) sum += ans[j] * a[i][j];
        if (abs(sum - a[i][m]) > EPS) return 0;
    }
    for (int x : w) if (x == -1) return 2;
    return 1;
}

//usage example
// int main() {
// 	Matrix<int, 3> A;
// 	A.d = {{{{1,2,3}}, {{4,5,6}}, {{7,8,9}}}};
// 	array<int, 3> vec = {1,2,3};
// 	vec = (A^10) * vec;
// }
