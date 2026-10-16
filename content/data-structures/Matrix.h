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

//usage example
// int main() {
// 	Matrix<int, 3> A;
// 	A.d = {{{{1,2,3}}, {{4,5,6}}, {{7,8,9}}}};
// 	array<int, 3> vec = {1,2,3};
// 	vec = (A^10) * vec;
// }
