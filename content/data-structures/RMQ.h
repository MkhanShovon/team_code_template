/**
 * Author: Johan Sannemo, pajenegod
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Range Minimum Queries on an array. Returns
 * min(V[a], V[a + 1], ... V[b - 1]) in constant time.
 * Usage:
 *  RMQ rmq(values);
 *  rmq.query(inclusive, exclusive);
 * Time: $O(|V| \log |V| + Q)$
 * Status: stress-tested
 */
#pragma once

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) { //arguements : 1 - number of levels, V - the array
		for (ll pw = 1, k = 1; pw * 2 <= len(V); pw *= 2, ++k) {
			jmp.emplace_back(len(V) - pw * 2 + 1);
			fls(j,0,len(jmp[k]) - 1)
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(ll a, ll b) { //// query for minimum on llerval [a, b)
		assert(a < b); // or return inf if a == b
		ll dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

int main() {
    vector<int> V = {10, 25, 3, 7, 2, 9, 1, 8};
    RMQ<int> rmq(V);
    int ans1 = rmq.query(1, 4); 
    cout << "Minimum in range [1, 3] is: " << ans1 << "\n"; // Output: 3
}
