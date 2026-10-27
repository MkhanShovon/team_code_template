#include <bits/stdc++.h>
using namespace std;
 
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define test int t;cin>>t;while(t--)
#define ll long long int
#define ld long double
#define ull unsigned long long
#define pl pair<ll,ll>
#define vl vector<ll>
#define dl deque<ll>
#define sl set<ll>
#define usl unordered_set<ll>
#define msl multiset<ll>
#define ml map<ll,ll>
#define mml multimap<ll,ll>
#define uml unordered_map<ll,ll>
#define vpl vector<pair<ll,ll>>
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define no cout << "NO" << endl
#define yes cout << "YES" << endl
#define all(x) x.begin(), x.end()
#define allr(a) a.rbegin(), a.rend()
#define endl "\n"
#define pi 3.14159265358979323846L
#define fixed(n) fixed << setprecision(n)
#define debug(x) cout << #x << ": " << (x) << "\n";



// segmented seive
vector<bool> segmentedSieve(ll L, ll R) {
    // generate all primes up to sqrt(R)
    ll lim = sqrt(R);
    vector<bool> mark(lim + 1, 0);
    vl primes;
    for (ll i = 2; i <= lim; ++i) {
        if (!mark[i]) {
            primes.emplace_back(i);
            for (ll j = i * i; j <= lim; j += i)
                mark[j] = 1;
        }
    }

    vector<bool> isPrime(R - L + 1, 1);
    for (ll i : primes)
        for (ll j = max(i * i, (L + i - 1) / i * i); j <= R; j += i)
            isPrime[j - L] = 0;
    if (L == 1)
        isPrime[0] = 0;
    return isPrime;
}