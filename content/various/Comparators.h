/**
 * Author: Monjur Hossain Khan, OpenAI Codex
 * License: CC0
 * Description: Small pair comparators for sorting and priority queues.
 * Time: O(1)
 * Status: tested
 */
#pragma once

bool firstAscSecondAsc(pii a, pii b) { return a.first == b.first ? a.second < b.second : a.first < b.first; }
bool firstAscSecondDesc(pii a, pii b) { return a.first == b.first ? a.second > b.second : a.first < b.first; }
bool firstDescSecondAsc(pii a, pii b) { return a.first == b.first ? a.second < b.second : a.first > b.first; }
bool firstDescSecondDesc(pii a, pii b) { return a.first == b.first ? a.second > b.second : a.first > b.first; }

struct PQFirstDescSecondAsc {
	bool operator()(pii a, pii b) const {
		return a.first != b.first ? a.first < b.first : a.second > b.second;
	}
};
