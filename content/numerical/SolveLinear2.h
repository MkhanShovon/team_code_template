/**
 * Author: Simon Lindholm
 * Date: 2016-09-06
 * License: CC0
 * Source: me
 * Description: To get all uniquely determined values of $x$ back from SolveLinear, make the following changes:
 * Status: tested on kattis:equationsolverplus, stress-tested
 */
#pragma once

#include "SolveLinear.h"

fl(j, n) if (j != i) // instead of fls(j, i+1, n - 1)
// ... then at the end:
x.assign(m, undefined);
fl(i, rank) {
	fls(j, rank, m - 1) if (fabs(A[i][j]) > eps) goto fail;
	x[col[i]] = b[i] / A[i][i];
fail:; }
