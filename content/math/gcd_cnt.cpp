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



// gcd cnt
const ll MM=1000001;
 
vl mob(ll m){
    vl mobb(m+1,0);
    mobb[1]=1;
    for(ll i=1;i<=m;i++){
        for(ll j=2*i;j<=m;j+=i){
            mobb[j]-=mobb[i];
        }
    }
    return mobb;
}
 
int main() {
    fastio;
    vl f(MM,0);
    ll n,a;
    cin >> n;
    vl freq(MM,0);
    ll m=-1;
    for(ll i=0;i<n;i++){
        cin >> a;
        freq[a]++;
        m=max(m,a);
    }
    for(ll i=1;i<=m;i++){
        for(ll j=i;j<=m;j+=i){
            f[i]+=freq[j];
        }
    }
    vl mobb=mob(m);
    // vl g(m+1);
    // for(ll i=m;i>0;i--){
    //     g[i]=f[i]*(f[i]-1)/2;
    //     for(ll j=2*i;j<=m;j+=i){
    //         g[i]-=g[j];
    //     }
    // }
    // cout << g[1] << endl;
    ll x=0;
    for(ll i=1;i<=m;i++) x+=mobb[i]*f[i]*(f[i]-1)/2;
    cout << x << endl;
 
 
    return 0;
}