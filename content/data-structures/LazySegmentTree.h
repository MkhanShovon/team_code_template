/**
 * Author: BUET_Orion
 * Date: 2026-10-23
 * License: CC0
 * Description: Generic lazy segment tree, half-open ranges $[l, r)$.
 * T value, U lazy tag; cq(T,T) combines values, cu(old U, new U) composes
 * tags, au(T,U,len) applies a tag to a node covering len elements.
 * iq / iu are the identities of cq / cu (iu must mean "no tag").
 * Usage: auto cq=[](ll a,ll b){return a+b;}; auto cu=cq;
 *  auto au=[](ll a,ll b,int len){return a+b*len;};       // add / sum
 *  LazySeg seg(n, 0LL, 0LL, cq, cu, au, a); seg.upd(l, r, v); seg.qry(l, r);
 *  // add/min: cq=min, iq=INF, au: a+b.  assign/sum: iu=NONE,
 *  // cu: b, au: b*len.  assign/min: cq=min, cu: b, au: b.
 * Time: O(\log N) per operation
 * Status: tested
 */
#pragma once

template<class T, class U, class F1, class F2, class F3> struct LazySeg {
	int n; vector<T> t; vector<U> d; T iq; U iu; F1 cq; F2 cu; F3 au;
	LazySeg(int sz_, T iq, U iu, F1 cq, F2 cu, F3 au, const vector<T>& a = {})
		: iq(iq), iu(iu), cq(cq), cu(cu), au(au) {
		for (n = 1; n < sz_; n *= 2);
		t.assign(2 * n, iq); d.assign(2 * n, iu);
		if (len(a)) build(a, 0, 0, n);
	}
	void push(int x, int lx, int rx) {
		if (d[x] == iu) return;
		t[x] = au(t[x], d[x], rx - lx);
		if (rx - lx > 1) fls(c, 1, 2) d[2*x+c] = cu(d[2*x+c], d[x]);
		d[x] = iu;
	}
	void pull(int x) { t[x] = cq(t[2*x+1], t[2*x+2]); }
	void build(const vector<T>& a, int x, int lx, int rx) {
		if (rx - lx == 1) { t[x] = lx < len(a) ? a[lx] : iq; return; }
		int m = (lx + rx) / 2;
		build(a, 2*x+1, lx, m), build(a, 2*x+2, m, rx), pull(x);
	}
	void upd(int l, int r, U v, int x, int lx, int rx) {
		push(x, lx, rx);
		if (lx >= r || l >= rx) return;
		if (l <= lx && rx <= r) { d[x] = cu(d[x], v); push(x, lx, rx); return; }
		int m = (lx + rx) / 2;
		upd(l, r, v, 2*x+1, lx, m), upd(l, r, v, 2*x+2, m, rx), pull(x);
	}
	void set(int i, T v, int x, int lx, int rx) {
		push(x, lx, rx);
		if (rx - lx == 1) { t[x] = v; return; }
		int m = (lx + rx) / 2;
		if (i < m) set(i, v, 2*x+1, lx, m), push(2*x+2, m, rx);
		else set(i, v, 2*x+2, m, rx), push(2*x+1, lx, m);
		pull(x);
	}
	T qry(int l, int r, int x, int lx, int rx) {
		push(x, lx, rx);
		if (lx >= r || l >= rx) return iq;
		if (l <= lx && rx <= r) return t[x];
		int m = (lx + rx) / 2;
		return cq(qry(l, r, 2*x+1, lx, m), qry(l, r, 2*x+2, m, rx));
	}
	void upd(int l, int r, U v) { upd(l, r, v, 0, 0, n); }
	void set(int i, T v) { set(i, v, 0, 0, n); }
	T qry(int l, int r) { return qry(l, r, 0, 0, n); }
};
