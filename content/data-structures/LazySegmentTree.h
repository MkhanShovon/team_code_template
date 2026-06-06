/**
 * Author: Unknown
 * Date: 2024-01-01
 * License: CC0
 * Source: own work
 * Description: Lazy segment tree supporting range updates and range queries.
 *   Parametrized by value type T, lazy type U, query combiner F1 (T,T)->T,
 *   lazy combiner F2 (U,U)->U, and apply function F3 (T,U,int)->T.
 *   \texttt{iq} is the identity for T, \texttt{iu} is the identity for U.
 * Time: O(\log N) per update/query
 * Status: tested
 */
#pragma once
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template <class T, class U, class F1, class F2, class F3>
struct LazySeg
{
	int n;
	vector<T> t;
	vector<U> d; // t=tree, d=delayed/lazy
	T iq; U iu; F1 cq; F2 cu; F3 au;
	LazySeg(int sz, T iq, U iu, F1 cq, F2 cu, F3 au,
			const vector<T> &a = {}) : iq(iq), iu(iu),
									   cq(cq), cu(cu), au(au)
	{
		for (n = 1; n < sz; n *= 2)
			;
		t.assign(2 * n, iq);
		d.assign(2 * n, iu);
		if (a.size())
			build(a, 0, 0, n);
	}
	void push(int x, int lx, int rx)
	{
		if (d[x] == iu)
			return;
		t[x] = au(t[x], d[x], rx - lx);
		if (rx - lx > 1)
		{
			d[2 * x + 1] = cu(d[2 * x + 1], d[x]);
			d[2 * x + 2] = cu(d[2 * x + 2], d[x]);
		}
		d[x] = iu;
	}
	void build(const vector<T> &a, int x, int lx, int rx)
	{
		if (rx - lx == 1)
		{
			t[x] = lx < (int)a.size() ? a[lx] : iq;
			return;
		}
		int m = (lx + rx) / 2;
		build(a, 2 * x + 1, lx, m);
		build(a, 2 * x + 2, m, rx);
		t[x] = cq(t[2 * x + 1], t[2 * x + 2]);
	}
	void upd(int l, int r, U v, int x, int lx, int rx)
	{
		push(x, lx, rx);
		if (lx >= r || l >= rx)
			return;
		if (lx >= l && rx <= r)
		{
			d[x] = cu(d[x], v);
			push(x, lx, rx);
			return;
		}
		int m = (lx + rx) / 2;
		upd(l, r, v, 2 * x + 1, lx, m);
		upd(l, r, v, 2 * x + 2, m, rx);
		t[x] = cq(t[2 * x + 1], t[2 * x + 2]);
	}
	void set(int i, T v, int x, int lx, int rx)
	{
		push(x, lx, rx);
		if (rx - lx == 1)
		{
			t[x] = v;
			return;
		}
		int m = (lx + rx) / 2;
		if (i < m)
			set(i, v, 2 * x + 1, lx, m);
		else
			set(i, v, 2 * x + 2, m, rx);
		t[x] = cq(t[2 * x + 1], t[2 * x + 2]);
	}
	T qry(int l, int r, int x, int lx, int rx)
	{
		push(x, lx, rx);
		if (lx >= r || l >= rx)
			return iq;
		if (lx >= l && rx <= r)
			return t[x];
		int m = (lx + rx) / 2;
		return cq(qry(l, r, 2 * x + 1, lx, m), qry(l, r, 2 * x + 2, m, rx));
	}
	void upd(int l, int r, U v) { upd(l, r, v, 0, 0, n); }
	void set(int i, T v) { set(i, v, 0, 0, n); }
	T qry(int l, int r) { return qry(l, r, 0, 0, n); }
/** Usage examples:
	 * // 1. Range Add / Range Sum
	 * auto cq_sum = [](ll a, ll b){ return a + b; };
	 * auto cu_add = [](ll a, ll b){ return a + b; };
	 * auto au_sum = [](ll a, ll b, int len){ return a + b * len; };
	 * LazySeg seg(n, 0LL, 0LL, cq_sum, cu_add, au_sum, a);
	 *
	 * // 2. Range Add / Range Min
	 * auto cq_min = [](ll a, ll b){ return min(a, b); };
	 * auto au_min = [](ll a, ll b, int len){ return a + b; };
	 * LazySeg seg(n, (ll)1e18, 0LL, cq_min, cu_add, au_min, a);
	 *
	 * // 3. Range Assign / Range Sum
	 * auto cu_set = [](ll a, ll b){ return b; };
	 * auto au_set = [](ll a, ll b, int len){ return b * len; };
	 * LazySeg seg(n, 0LL, -1LL, cq_sum, cu_set, au_set, a);
 */
};

