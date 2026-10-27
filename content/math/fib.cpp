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



// fast double method (return F_n,F_{n+1})
pl fib(ll n){
    if(n==0) return {0,1};

    auto p=fib(n>>1);
    ll c= p.ff*(2*p.ss-p.ff);
    ll d=p.ff*p.ff+p.ss*p.ss;
    if(n&1) return {d, c + d};
    else return {c, d};
}

ll fall(ll n){
    if(n>=0) return fib(n).ff;
    else{
        n=-n;
        if(n%2==0) return -fib(n).ff;
        else return fib(n).ff;
    }
}

// different based fib
ll fibdif(ll i,ll fi,ll j,ll fj,ll n){
    ll a,b;
    ll ci1=fall(i),ci2=fall(i-1),cj1=fall(j),cj2=fall(j-1);
    ll d=ci1*cj2-ci2*cj1;
    ll f0=(fi*cj2-fj*ci2)/d,f1=-(fi*cj1-fj*ci1)/d;
    ll fn=f0*fall(n)+f1*fall(n-1);
    return fn;
}