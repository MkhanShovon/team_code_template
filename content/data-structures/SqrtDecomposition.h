/**
 * Author: Monjur Hossain Khan, OpenAI Codex
 * License: CC0
 * Description: Sqrt decomposition with range add and range sum queries.
 * Ranges are zero-indexed and inclusive: [l, r].
 * Time: O(\sqrt N) per operation.
 * Status: tested
 */
#pragma once

struct SqrtRangeAdd {
	int n, B;
	vector<ll> a, lazy, sum;
	SqrtRangeAdd(const vector<ll>& v = {}) { init(v); }
	void init(const vector<ll>& v) {
		a = v; n = len(a); B = max(1, (int)sqrt(max(1, n)));
		lazy.assign((n + B - 1) / B, 0);
		sum.assign(len(lazy), 0);
		fl(i, n) sum[i / B] += a[i];
	}
	void add(int l, int r, ll x) {
		int bl = l / B, br = r / B;
		if (bl == br) {
			fls(i, l, r) a[i] += x, sum[bl] += x;
			return;
		}
		fls(i, l, min(n, (bl + 1) * B) - 1) a[i] += x, sum[bl] += x;
		fls(b, bl + 1, br - 1) lazy[b] += x;
		fls(i, br * B, r) a[i] += x, sum[br] += x;
	}
	ll get(int i) { return a[i] + lazy[i / B]; }
	ll query(int l, int r) {
		ll ans = 0;
		int bl = l / B, br = r / B;
		if (bl == br) {
			fls(i, l, r) ans += get(i);
			return ans;
		}
		fls(i, l, min(n, (bl + 1) * B) - 1) ans += get(i);
		fls(b, bl + 1, br - 1) ans += sum[b] + lazy[b] * min(B, n - b * B);
		fls(i, br * B, r) ans += get(i);
		return ans;
	}
};

int main() {
    vector<ll> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    SqrtRangeAdd sq(arr);
    cout << "Initial sum [1, 3]: " << sq.query(1, 3) << "\n"; 
    sq.add(2, 5, 10);
    cout << "Sum [1, 3] after adding 10 to [2, 5]: " << sq.query(1, 3) << "\n";
    cout << "Value at index 4: " << sq.get(4) << "\n";
}