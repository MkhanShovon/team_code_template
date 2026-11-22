/**
 * Author: Monjur Hossain Khan, OpenAI Codex
 * License: CC0
 * Description: Small pair comparators for sorting and priority queues.
 * Time: O(1)
 * Status: tested
 */
#pragma once

bool firstAscSecondAsc(pair<ll, ll> a, pair<ll, ll> b) { return a.first == b.first ? a.second < b.second : a.first < b.first; }
bool firstAscSecondDesc(pair<ll, ll> a, pair<ll, ll> b) { return a.first == b.first ? a.second > b.second : a.first < b.first; }
bool firstDescSecondAsc(pair<ll, ll> a, pair<ll, ll> b) { return a.first == b.first ? a.second < b.second : a.first > b.first; }
bool firstDescSecondDesc(pair<ll, ll> a, pair<ll, ll> b) { return a.first == b.first ? a.second > b.second : a.first > b.first; }

struct PQFirstDescSecondAsc {
	bool operator()(pair<ll, ll> a, pair<ll, ll> b) const {
		return a.first != b.first ? a.first < b.first : a.second > b.second;
	}
};
