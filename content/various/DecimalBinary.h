/**
 * Author: Monjur Hossain Khan, OpenAI Codex
 * License: CC0
 * Description: Decimal/binary conversion helpers.
 * Time: O(log n) for dec->bin, O(|s|) for bin->dec.
 * Status: tested
 */
#pragma once

string decToBinary(long long n) {
	if (n == 0) return "0";
	string s = "";
	while (n > 0) {
		s = to_string(n % 2) + s;
		n = n / 2;
	}
	return s;
}

long long binaryToDecimal(const string& n) {
	long long dec_value = 0;
	long long base = 1;
	for (int i = (int)n.length() - 1; i >= 0; --i) {
		if (n[i] == '1') dec_value += base;
		base = base * 2;
	}
	return dec_value;
}
