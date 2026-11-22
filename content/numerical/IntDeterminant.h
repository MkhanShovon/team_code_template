/**
 * Author: Unknown
 * Date: 2014-11-27
 * Source: somewhere on github
 * Description: Calculates determinant using modular arithmetics.
 * Modulos can also be removed to get a pure-integer version.
 * Time: $O(N^3)$
 * Status: bruteforce-tested for N <= 3, mod <= 7
 */
#pragma once

const ll mod = 12345;
ll det(vector<vector<ll>>& a) {
	int n = len(a); ll ans = 1;
	fl(i, n) {
		fls(j, i+1, n - 1) {
			while (a[j][i] != 0) { // gcd step
				ll t = a[i][i] / a[j][i];
				if (t) fls(k, i, n - 1)
					a[i][k] = (a[i][k] - a[j][k] * t) % mod;
				swap(a[i], a[j]);
				ans *= -1;
			}
		}
		ans = ans * a[i][i] % mod;
		if (!ans) return 0;
	}
	return (ans + mod) % mod;
}
