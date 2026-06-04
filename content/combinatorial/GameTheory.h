/**
 * Author: Monjur Hossain Khan, OpenAI Codex
 * License: CC0
 * Description: Basic impartial game helpers: Nim, misere Nim,
 * staircase Nim, and subtraction-game Grundy numbers.
 * Time: O(N|moves|) for subtraction Grundy.
 * Status: tested
 */
#pragma once

bool nimWin(const vi& piles) {
	int x = 0;
	for (int p : piles) x ^= p;
	return x != 0;
}
bool misereNimWin(const vi& piles) {
	int x = 0, ones = 0, mx = 0;
	for (int p : piles) x ^= p, ones += p == 1, mx = max(mx, p);
	return mx <= 1 ? ones % 2 == 0 : x != 0;
}
bool staircaseNimWin(const vi& piles, int firstRelevant = 1) {
	int x = 0;
	for (int i = firstRelevant; i < sz(piles); i += 2) x ^= piles[i];
	return x != 0;
}
vi subtractionGrundy(int N, vi moves) {
	vi g(N + 1), seen(sz(moves) + 1);
	rep(i,1,N + 1) {
		for (int s : moves) if (i >= s && g[i - s] < sz(seen))
			seen[g[i - s]] = i;
		while (seen[g[i]] == i) g[i]++;
	}
	return g;
}
