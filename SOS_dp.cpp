 #include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define fast_io ios::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
ll inf=1e18;
const int M=1e9+7;
#define pb push_back

long long binpow(long long a, long long b, long long m) {
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

int lg = 20;
ll lim = 1 << lg;
vector<ll> dpsub(lim), dpsup(lim);
vector<int> freq(lim);

void sos_sub() {
    // stores the number of subsets of mask in dpsub[mask]
    for(int i = 0; i < lim; i++) dpsub[i] = freq[i];
    for(int i = 0; i < lg; i++) {
        for(int mask = 0; mask < lim; mask++) {
            if(mask & (1 << i)) dpsub[mask] += dpsub[mask ^ (1 << i)];
        }
    }
}

void sos_sup() {
    // stores the number of supersets of mask in dpsup[mask]
    for(int i = 0; i < lim; i++) dpsup[i] = freq[i];
    for(int i = 0; i < lg; i++) {
        for(int mask = 0; mask < lim; mask++) {
            if(mask & (1 << i)) dpsup[mask ^ (1 << i)] += dpsup[mask];
        }
    }
}

void sos_sub_backward() {
    // undo of fwd
    for(int i = 0; i < lg; i++) {
        for(int mask = lim - 1; mask >= 0; mask--) {
            if(mask & (1 << i)) dpsub[mask] -= dpsub[mask ^ (1 << i)];
        }
    }
}

void sos_sup_backward() {
    // undo of fwd
    for(int i = 0; i < lg; i++) {
        for(int mask = lim - 1; mask >= 0; mask--) {
            if(mask & (1 << i)) dpsup[mask ^ (1 << i)] = (dpsup[mask ^ (1 << i)] - dpsup[mask] + M) % M;
        }
    }
}

void solvecses() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &i : a) cin >> i, freq[i]++;
    sos_sub();
    sos_sup();
    for(int i = 0; i < n; i++) {
        cout << dpsub[a[i]] << " " << dpsup[a[i]] << " " << n - dpsub[(lim - 1) ^ a[i]]  << endl;
    }
} 

void solve() {
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        freq[x]++;
    }
    sos_sup();
    for(int i = 0; i < lim; i++) {
        // dpsup[i] %= M;
        dpsup[i] = binpow(2, dpsup[i], M) - 1;
    }
    sos_sup_backward();
    cout << dpsup[0] << endl;
}
 
int main() {
    fast_io
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
    return 0;
}