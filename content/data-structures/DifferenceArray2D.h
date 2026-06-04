/**
 * Author: Monjur Hossain Khan, OpenAI Codex
 * License: CC0
 * Description: 2D difference array for rectangle add and point values.
 * Coordinates are zero-indexed, rectangles are [r1, r2) x [c1, c2).
 * Time: $O(1)$ update, $O(HW)$ build.
 * Status: tested
 */
#pragma once

template<class T>
struct Diff2D {
	int H, W;
	vector<vector<T>> d;
	Diff2D(int H, int W) : H(H), W(W), d(H + 1, vector<T>(W + 1)) {}
	void add(int r1, int c1, int r2, int c2, T v) {
		if (r1 >= r2 || c1 >= c2) return;
		d[r1][c1] += v; d[r1][c2] -= v;
		d[r2][c1] -= v; d[r2][c2] += v;
	}
	vector<vector<T>> build() {
		vector<vector<T>> a(H, vector<T>(W));
		rep(i,0,H) rep(j,0,W) {
			T up = i ? a[i - 1][j] : T();
			T left = j ? a[i][j - 1] : T();
			T diag = i && j ? a[i - 1][j - 1] : T();
			a[i][j] = d[i][j] + up + left - diag;
		}
		return a;
	}
};
