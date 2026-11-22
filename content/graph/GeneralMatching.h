/**
 * Author: Simon Lindholm
 * Date: 2016-12-09
 * License: CC0
 * Source: http://www.mimuw.edu.pl/~mucha/pub/mucha_sankowski_focs04.pdf
 * Description: Matching for general graphs.
 * Fails with probability $N / mod$.
 * Time: O(N^3)
 * Status: not very well tested
 */
#pragma once

#include "../numerical/MatrixInverse-mod.h"

vector<pair<ll, ll>> generalMatching(int N, vector<pair<ll, ll>>& ed) {
	vector<vector<ll>> mat(N, vector<ll>(N)), A;
	for (pair<ll, ll> pa : ed) {
		int a = pa.first, b = pa.second, r = rand() % mod;
		mat[a][b] = r, mat[b][a] = (mod - r) % mod;
	}

	int r = matInv(A = mat), M = 2*N - r, fi, fj;
	assert(r % 2 == 0);

	if (M != N) do {
		mat.resize(M, vector<ll>(M));
		fl(i, N) {
			mat[i].resize(M);
			fls(j, N, M - 1) {
				int r = rand() % mod;
				mat[i][j] = r, mat[j][i] = (mod - r) % mod;
			}
		}
	} while (matInv(A = mat) != M);

	vll has(M, 1); vector<pair<ll, ll>> ret;
	fl(it, M/2) {
		fl(i, M) if (has[i])
			fls(j, i+1, M - 1) if (A[i][j] && mat[i][j]) {
				fi = i; fj = j; goto done;
		} assert(0); done:
		if (fj < N) ret.emplace_back(fi, fj);
		has[fi] = has[fj] = 0;
		fl(sw, 2) {
			ll a = modpow(A[fi][fj], mod-2);
			fl(i, M) if (has[i] && A[i][fj]) {
				ll b = A[i][fj] * a % mod;
				fl(j, M) A[i][j] = (A[i][j] - A[fi][j] * b) % mod;
			}
			swap(fi,fj);
		}
	}
	return ret;
}
