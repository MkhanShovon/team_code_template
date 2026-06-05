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

// Inverse Transform (Mobius) - recover A from F (use inverse=true in sosSubsets/sosSupersets)
// for (int i = 0; i < (1<<N); i++) A[i] = F[i];
// for (int bit = 0; bit < N; bit++)
//     for (int mask = 0; mask < (1<<N); mask++)
//         if (mask & (1<<bit))
//             F[mask] -= F[mask ^ (1<<bit)];