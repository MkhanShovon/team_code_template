#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
// #pragma GCC optimize("O3,unroll-loops") // put above includes
template <class T> using oset = tree<T, null_type, less<T>,
	rb_tree_tag, tree_order_statistics_node_update>;
// order_of_key(x): # < x, *find_by_order(k): k-th (0-idx)
// multiset: oset<pair<T,int>> with a unique id as .second

typedef long long ll;
using ull = unsigned long long; using lld = long double;
using i128 = __int128_t; using vll = vector<ll>;
#define fl(i, n) for (ll i = 0; i < (n); i++)
#define fls(i, m, n) for (ll i = (m); i <= (n); i++)
#define rl(i, m, n) for (ll i = (n); i >= (m); i--)
#define vr(v) (v).begin(), (v).end()
#define rv(v) (v).rbegin(), (v).rend()
#define len(v) (ll)(v).size()
#define edl '\n'
template <class T> istream& operator>>(istream& is, vector<T>& v) {
	for (auto& x : v) is >> x;
	return is;
}
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

void solve() {
}
int main() {
	cin.tie(0)->sync_with_stdio(0);
	int t = 1; // cin >> t;
	while (t--) solve();
}
