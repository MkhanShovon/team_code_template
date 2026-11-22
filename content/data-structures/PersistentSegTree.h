/**
 * Author: BUET_Orion (adapted from youknowwho)
 * Date: 2026-11-22
 * License: CC0
 * Description: Persistent point-add / range-sum segment tree on $[0, n)$.
 * Version 0 is the empty tree (node 0). Every upd returns a new root.
 * kth(ra, rb, k): smallest pos s.t. (sum of rb - sum of ra) on $[0,pos]$ $> k$,
 * i.e. the k-th (0-indexed) smallest compressed value in a[l, r) if
 * root[i+1] = upd(root[i], a[i], 1).
 * Usage: PST t(n); vll root{0};
 *  for (int x : a) root.push_back(t.upd(root.back(), x, 1));
 *  t.kth(root[l], root[r], k); t.query(root[r], L, R) - t.query(root[l], L, R);
 * Time: O(\log N) per operation, O(\log N) new nodes per update.
 * Status: stress-tested
 */
#pragma once

struct PST {
	struct Node { int l = 0, r = 0; ll s = 0; };
	vector<Node> t; int n;
	PST(int n) : t(1), n(n) { t.reserve(n * 20); }
	int upd(int v, int pos, ll x, int lo = 0, int hi = -1) {
		if (hi < 0) hi = n;
		int u = len(t); t.push_back(t[v]); t[u].s += x;
		if (hi - lo > 1) {
			int m = (lo + hi) / 2, c;
			if (pos < m) c = upd(t[v].l, pos, x, lo, m), t[u].l = c;
			else c = upd(t[v].r, pos, x, m, hi), t[u].r = c;
		}
		return u;
	}
	ll query(int v, int L, int R, int lo = 0, int hi = -1) {
		if (hi < 0) hi = n; // sum on [L, R)
		if (!v || R <= lo || hi <= L) return 0;
		if (L <= lo && hi <= R) return t[v].s;
		int m = (lo + hi) / 2;
		return query(t[v].l, L, R, lo, m) + query(t[v].r, L, R, m, hi);
	}
	int kth(int a, int b, ll k) {
		int lo = 0, hi = n;
		while (hi - lo > 1) {
			int m = (lo + hi) / 2;
			ll c = t[t[b].l].s - t[t[a].l].s;
			if (k < c) a = t[a].l, b = t[b].l, hi = m;
			else k -= c, a = t[a].r, b = t[b].r, lo = m;
		}
		return lo;
	}
};
