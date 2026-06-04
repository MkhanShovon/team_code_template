/**
 * Author: Monjur Hossain Khan, OpenAI Codex
 * License: CC0
 * Description: Common binomial helpers: nCr modulo a prime, exact small nCr,
 * Lucas theorem, Catalan numbers, derangements, and Stirling numbers.
 * Time: O(N) preprocessing, O(1) nCr, O(\log_p N) Lucas.
 * Status: tested
 */
#pragma once

ll modPowComb(ll a, ll e, ll m) {
	ll r = 1 % m;
	for (a %= m; e; e >>= 1, a = a * a % m) if (e & 1) r = r * a % m;
	return r;
}

struct CombMod {
	int mod;
	vector<ll> fact, ifact;
	CombMod(int n = 0, int mod = 1000000007) : mod(mod), fact(n + 1), ifact(n + 1) {
		fact[0] = 1;
		if (!n) { ifact[0] = 1; return; }
		rep(i,1,n + 1) fact[i] = fact[i - 1] * i % mod;
		ifact[n] = modPowComb(fact[n], mod - 2, mod);
		for (int i = n; i; --i) ifact[i - 1] = ifact[i] * i % mod;
	}
	ll C(ll n, ll k) const {
		if (k < 0 || k > n || n >= sz(fact)) return 0;
		return fact[n] * ifact[k] % mod * ifact[n - k] % mod;
	}
	ll lucas(ll n, ll k) const {
		if (k < 0 || k > n) return 0;
		ll r = 1;
		while (n || k) {
			r = r * C(n % mod, k % mod) % mod;
			n /= mod; k /= mod;
		}
		return r;
	}
};

ll combExact(int n, int k) {
	if (k < 0 || k > n) return 0;
	k = min(k, n - k);
	ll r = 1;
	rep(i,1,k + 1) r = r * (n - k + i) / i;
	return r;
}
bool binomOdd(ll n, ll k) { return (n & k) == k; }

vi catalanDP(int n, int mod) {
	vi C(n + 1); C[0] = 1;
	rep(i,1,n + 1) rep(j,0,i) C[i] = (C[i] + (ll)C[j] * C[i - 1 - j]) % mod;
	return C;
}
vi derangements(int n, int mod) {
	vi D(n + 1); D[0] = 1;
	if (n) D[1] = 0;
	rep(i,2,n + 1) D[i] = (ll)(i - 1) * (D[i - 1] + D[i - 2]) % mod;
	return D;
}
vector<vi> stirling2(int n, int k, int mod) {
	vector<vi> S(n + 1, vi(k + 1));
	S[0][0] = 1;
	rep(i,1,n + 1) rep(j,1,min(i, k) + 1)
		S[i][j] = (S[i - 1][j - 1] + (ll)j * S[i - 1][j]) % mod;
	return S;
}
