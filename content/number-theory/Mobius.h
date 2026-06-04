/**
 * Author: Monjur Hossain Khan, OpenAI Codex
 * License: CC0
 * Description: Linear sieve for the Mobius function.
 * Time: O(N)
 * Status: tested
 */
#pragma once

vi mobiusSieve(int n) {
	vi mu(n + 1), lp(n + 1), primes;
	mu[1] = 1;
	rep(i,2,n + 1) {
		if (!lp[i]) lp[i] = i, primes.push_back(i), mu[i] = -1;
		for (int p : primes) {
			if (p > lp[i] || i * p > n) break;
			lp[i * p] = p;
			if (p == lp[i]) { mu[i * p] = 0; break; }
			mu[i * p] = -mu[i];
		}
	}
	return mu;
}
