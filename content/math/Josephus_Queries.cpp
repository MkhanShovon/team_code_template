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




// Josephus Queries
ll f(ll n,ll k){
    if(n==1) return 1;
    if(k<=(n+1)/2){
        if(2*k>n) return 1;
        else return 2*k;
    }
    ll x=f(n/2,k-(n+1)/2);
    if(n&1) return 2*x+1;
    else return 2*x-1;
}