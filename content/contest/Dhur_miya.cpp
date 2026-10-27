#include <bits/stdc++.h>
using namespace std;
 
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
#include <ext/rope>
using namespace __gnu_cxx;
using namespace __gnu_pbds;
 
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define test int t;cin>>t;while(t--)
#define ll long long int
#define ld long double
#define ull unsigned long long
#define pl pair<ll,ll>
#define vl vector<ll>
#define vvl vector<vl>
#define dl deque<ll>
#define sl set<ll>
#define usl unordered_set<ll>
#define msl multiset<ll>
#define ml map<ll,ll>
#define mml multimap<ll,ll>
#define uml unordered_map<ll,ll,custom_hash>
#define vpl vector<pair<ll,ll>>
#define pb push_back
#define pf push_front
#define mp make_pair
#define ff first
#define ss second
#define no cout << "NO" << endl
#define yes cout << "YES" << endl
#define alice cout << "Alice" << endl
#define bob cout << "Bob" << endl
#define all(x) x.begin(), x.end()
#define allr(a) a.rbegin(), a.rend()
#define endl "\n"
#define pi 3.14159265358979323846L
#define fixed(n) fixed << setprecision(n)
#define debug(x) cout << #x << ": " << (x) << "\n";

// Macros
#define fl(i, n) for (ll i = 0; i < n; i++)
#define fls(i, m, n) for (ll i = m; i <= n; i++)
#define rl(i, m, n) for (ll i = n; i >= m; i--)
#define vr(v) v.begin(), v.end()
#define rv(v) v.rbegin(), v.rend()
#define edl '\n'
#define len(v) v.size()
#define nl cout << edl;
 
#define checkbit(x,n) (x&(1LL<<n))
#define setbit(x,n) (x=(x|(1LL<<n)))
#define resetbit(x,n) (x=(x&(~(1LL<<n))))
 
template<typename T> void get(T&a){for(auto&e:a)cin>>e;}
template<typename T> void put(T a){for(auto e:a)cout<<e<<" ";cout<<endl;}
 
 
template<class T> using ordered_set = tree<T,null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
template<class T> using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;




struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }
 
    template<typename T>
    size_t operator()(const T& v) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(static_cast<uint64_t>(std::hash<T>{}(v)) + FIXED_RANDOM);
    }
 
    template<class T1, class T2>
    size_t operator()(const pair<T1,T2>& p) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        uint64_t h1 = splitmix64(static_cast<uint64_t>(std::hash<T1>{}(p.first)) + FIXED_RANDOM);
        uint64_t h2 = splitmix64(static_cast<uint64_t>(std::hash<T2>{}(p.second)) + FIXED_RANDOM);
        return h1 ^ (h2 << 1);
    }
 
    template<class... Ts>
    size_t operator()(const tuple<Ts...>& t) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return apply([&](const auto&... elems) {
            size_t h = 0;
            ((h ^= splitmix64(static_cast<uint64_t>(std::hash<std::decay_t<decltype(elems)>>{}(elems)) + FIXED_RANDOM)), ...);
            return h;
        }, t);
    }
};



long long lrand(){
	long long i,x=0;
	for(i=0;i<4;i++)x=(x*32768+rand()%32768);
	return x;
}



// const ll M=1e9+7;
const ll INF=1e18;
const ll M=998244353;
// const ll M=1e8+7;
// const ll M=1000003;
 
 
 
bool comp(pl a,pl b){
 
    if(a.ss!=b.ss) return a.ss<b.ss;
    return a.ff<b.ff;
 
}
 

template<class T>
vl nextGreater(const vector<T>& a, bool strict = true) {
	vl res(a.size(), a.size()), st;
	for(ll i=0;i<a.size();i++) {
		while (!st.empty() && (strict ? a[i] > a[st.back()] : a[i] >= a[st.back()]))
			res[st.back()] = i, st.pop_back();
		st.push_back(i);
	}
	return res;
}
template<class T>
vl prevGreater(const vector<T>& a, bool strict = true) {
	vl res(a.size(), -1), st;
	for(ll i=0;i<a.size();i++) {
		while (!st.empty() && (strict ? a[i] >= a[st.back()] : a[i] > a[st.back()]))
			st.pop_back();
		if (!st.empty()) res[i] = st.back();
		st.push_back(i);
	}
	return res;
}


// const ll N=15e6+15;

// vl sp(N);
// vl p;


// void sieve(){
    
//     for(ll i=2;i<N;i++){
        
//         if(sp[i]) continue;
//         p.pb(i);
//         for(ll j=i;j<N;j+=i){
            
//             if(sp[j]) continue;
//             sp[j]=i;
//         }
        
//     }
    
//     return;
    
// }



ll mod(ll a,ll b){
    if(b==0) return 1%M;
    a=a%M; 
    
    __int128 x=mod(a,b/2);
    x=(x*x)%M;
    
    if(b&1) return (a*x)%M;
    else return x;
}

 
ll inverse_mod(ll b){return mod(b,M-2);}


// const ll N=3e5+10;
// vl fact(N,0);
 
// vl invfact(N,0);
 
// void factf(){
 
//     fact[0]=1;
//     for(ll i=1;i<N;i++){
//         fact[i]=(fact[i-1]*i)%M;
//         // invfact[i]=inverse_mod(fact[i]);
//     }
 
//     invfact[0]=1;
    
    
//     invfact[N-1]=inverse_mod(fact[N-1]);
    
//     for(ll i=N-2;i>=1;i--){
        
//         invfact[i]=((invfact[i+1]*(i+1))%M);
//     }
 
 
//     return;
// }
 
 
// ll ncr(ll n,ll r){
//     if(n<r) return 0;
//     if(r==0||r==n) return 1;
//     if(r==1||r==n-1) return (n)%M;
 
    
//     return (fact[n]*((invfact[r]*invfact[n-r])%M))%M;
// }

// const ll N=1e5+10;
// vl phi(N+1);
 
// void phif(void){
//     for(ll i=0;i<=N;i++) phi[i]=i;
//     for(ll i=2;i<=N;i++) if(phi[i]==i) for(ll j=i;j<=N;j+=i) phi[j]-=phi[j]/i;
// }



ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
ll lcm(ll a,ll b){return a/gcd(a,b)*b;}


struct DSU{
    ll n;
    vl parent,sz,score;
    
    DSU(ll n):n(n),parent(n),sz(n, 1),score(n,0){
        iota(all(parent),0); // parent[i] = i
    }
 
    ll find(ll x){
        
        while(x!=parent[x]) x=parent[x];
        return x;
        
        // if(parent[x]==x) return x;
        // return parent[x]=find(parent[x]); // path compression
    }
 
    bool unite(ll a,ll b) {
        a=find(a);
        b=find(b);
        if(a==b) return 0; // already in same set
        if(sz[a]<sz[b]) swap(a,b); // union by size
        // if(a>b) swap(a,b);
        
        parent[b]=a;
        sz[a]+=sz[b];
        
        score[b]-=score[a];
        
        return 1;
    }
 
    bool same(ll a,ll b) {
        return find(a)==find(b);
    }
 
    ll size(ll x) {
        return sz[find(x)];
    }
    
    void add(ll a,ll x){
        score[find(a)]+=x;
        return;
    }
    
    ll get(ll a){
        
        ll x=score[a];
        while(a!=parent[a]){
            a=parent[a];
            x+=score[a];
        }
        
        return x;
        
    }
 
};


// // derangement
// vl dp(N,-1);
// ll f(ll n){
//     if(n==1) return dp[n]=0;
//     if(n==2) return dp[n]=1;
//     if(dp[n]!=-1) return dp[n];
//     return dp[n]=((n-1)*((f(n-1)+f(n-2))%M))%M;
// }


struct P{
    ld x,y;
    bool operator<(P a){
        return x<a.x||(x==a.x&&y<a.y);
    }
    
    P operator+(const P& p) const{
        return P{x+p.x,y+p.y};
    }
    
    P operator-(const P& p) const{
        return P{x-p.x,y-p.y};
    }
    
    ld cross(const P& p) const{
        return x*p.y-y*p.x;
    }
    
};

ld cross(P o,P a,P b){
    
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
    
}

ld dot(P o,P a,P b){
    
    return (a.x-o.x)*(b.x-o.x)+(a.y-o.y)*(b.y-o.y);
    
}

ld dist(P a,P b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}


vector<P> convex_hull(vector<P> v){
    
    // ll n=v.size();
    ll k=0;
    
    
    sort(all(v));
    ll n=v.size();
    
    if(n<3) return v;
    
    vector<P> ans(2*n);
    
    
    for(ll i=0;i<n;i++){
        while(k>=2&&cross(ans[k-2],ans[k-1],v[i])<=0) k--;
        ans[k++]=v[i];
    }
    
    ll nn=k+1;
    for(ll i=n-2;i>=0;i--){
        while(k>=nn&&cross(ans[k-2],ans[k-1],v[i])<=0) k--;
        ans[k++]=v[i];
    }
    
    ans.resize(k-1);
    
    return ans;
    
    
}


// // DSA

// const ll MOD=M;


// struct segmentTree {
//     ll n;
//     vl sum, sum2;
//     vl lazy_add, lazy_set;
//     vector<bool> has_set;

//     // 1. PULL: Merge children into parent
//     void pull(ll v) {
//         ll lc = 2 * v, rc = 2 * v + 1;
//         sum[v] = sum[lc] + sum[rc];
//         sum2[v] = (sum2[lc] + sum2[rc]) % MOD;
//     }

//     // 2. LAZY HELPERS & PUSH
//     void apply_set(ll v, ll tl, ll tr, ll val) {
//         ll len = tr - tl + 1;
//         ll v_mod = (val % MOD + MOD) % MOD;

//         sum[v] = val * len;
//         sum2[v] = (((v_mod * v_mod) % MOD) * (len % MOD)) % MOD;

//         has_set[v] = true;
//         lazy_set[v] = val;
//         lazy_add[v] = 0; // Overwrite any pending additions
//     }

//     void apply_add(ll v, ll tl, ll tr, ll add) {
//         ll len = tr - tl + 1;
//         ll d_mod = (add % MOD + MOD) % MOD;
//         ll s_mod = (sum[v] % MOD + MOD) % MOD;

//         // Math: sum((x + d)^2) = sum(x^2) + 2*d*sum(x) + len*d^2
//         sum2[v] = (sum2[v] + (2 * d_mod % MOD) * s_mod + ((d_mod * d_mod) % MOD) * (len % MOD)) % MOD;
//         sum[v] += add * len;

//         if (has_set[v]) lazy_set[v] += add;
//         else lazy_add[v] += add;
//     }

//     void push(ll v, ll tl, ll tr) {
//         if (tl == tr) return;
//         ll m = (tl + tr) / 2;
//         if (has_set[v]) {
//             apply_set(2 * v, tl, m, lazy_set[v]);
//             apply_set(2 * v + 1, m + 1, tr, lazy_set[v]);
//             has_set[v] = false;
//         }
//         if (lazy_add[v] != 0) {
//             apply_add(2 * v, tl, m, lazy_add[v]);
//             apply_add(2 * v + 1, m + 1, tr, lazy_add[v]);
//             lazy_add[v] = 0;
//         }
//     }

//     // 3. BUILD & INIT
//     void set_leaf(ll v, ll x) {
//         sum[v] = x;
//         ll x_mod = (x % MOD + MOD) % MOD;
//         sum2[v] = (x_mod * x_mod) % MOD;
//     }

//     void build(vl& a, ll v, ll tl, ll tr) {
//         if (tl == tr) { set_leaf(v, a[tl]); return; }
//         ll m = (tl + tr) / 2;
//         build(a, 2 * v, tl, m);
//         build(a, 2 * v + 1, m + 1, tr);
//         pull(v);
//     }

//     void init(vl& a) {
//         n = a.size();
//         sum.assign(4 * n, 0);
//         sum2.assign(4 * n, 0);

//         lazy_add.assign(4 * n, 0);
//         lazy_set.assign(4 * n, 0);
//         has_set.assign(4 * n, false);

//         build(a, 1, 0, n - 1);
//     }

//     // 4. UPDATES: Point Update, Range Add, Range Set
//     void update(ll v, ll tl, ll tr, ll i, ll x) {
//         push(v, tl, tr);
//         if (i < tl || i > tr) return;
//         if (tl == tr) { set_leaf(v, x); return; }
//         ll m = (tl + tr) / 2;
//         update(2 * v, tl, m, i, x);
//         update(2 * v + 1, m + 1, tr, i, x);
//         pull(v);
//     }
//     void update(ll i, ll x) { update(1, 0, n - 1, i, x); }

//     void range_add(ll v, ll tl, ll tr, ll l, ll r, ll addend) {
//         push(v, tl, tr);
//         if (r < tl || l > tr) return;
//         if (l <= tl && tr <= r) { apply_add(v, tl, tr, addend); return; }
//         ll m = (tl + tr) / 2;
//         range_add(2 * v, tl, m, l, r, addend);
//         range_add(2 * v + 1, m + 1, tr, l, r, addend);
//         pull(v);
//     }
//     void range_add(ll l, ll r, ll addend) { range_add(1, 0, n - 1, l, r, addend); }

//     void range_set(ll v, ll tl, ll tr, ll l, ll r, ll val) {
//         push(v, tl, tr);
//         if (r < tl || l > tr) return;
//         if (l <= tl && tr <= r) { apply_set(v, tl, tr, val); return; }
//         ll m = (tl + tr) / 2;
//         range_set(2 * v, tl, m, l, r, val);
//         range_set(2 * v + 1, m + 1, tr, l, r, val);
//         pull(v);
//     }
//     void range_set(ll l, ll r, ll val) { range_set(1, 0, n - 1, l, r, val); }

//     // 5. QUERIES
//     ll getSum(ll v, ll tl, ll tr, ll l, ll r) {
//         push(v, tl, tr);
//         if (r < tl || l > tr) return 0;
//         if (l <= tl && tr <= r) return sum[v];
//         ll m = (tl + tr) / 2;
//         return getSum(2 * v, tl, m, l, r) + getSum(2 * v + 1, m + 1, tr, l, r);
//     }
//     ll getSum(ll l, ll r) { return getSum(1, 0, n - 1, l, r); }

//     ll getSum2(ll v, ll tl, ll tr, ll l, ll r) {
//         push(v, tl, tr);
//         if (r < tl || l > tr) return 0;
//         if (l <= tl && tr <= r) return sum2[v];
//         ll m = (tl + tr) / 2;
//         return (getSum2(2 * v, tl, m, l, r) + getSum2(2 * v + 1, m + 1, tr, l, r)) % MOD;
//     }
//     ll getSum2(ll l, ll r) { return getSum2(1, 0, n - 1, l, r); }
// };



// struct segmentTree{
    
//     ll n;
//     vl mask;
    
//     void pull(ll v){
        
//         mask[v]=mask[2*v]|mask[2*v+1];
        
//     }
    
//     void build(string& s,ll v,ll tl,ll tr){
//         if(tl==tr){
//             mask[v]|=(1LL<<(s[tl]-'a'));
//             return;
//         }
        
//         ll m=(tl+tr)/2;
//         build(s,2*v,tl,m);
//         build(s,2*v+1,m+1,tr);
//         pull(v);
        
//     }
    
//     void init(string& s){
        
//         n=s.size();
//         mask.assign(4*n,0);
//         build(s,1,0,n-1);
        
//     }
    
    
//     void update(ll v,ll tl,ll tr,ll l,char c){
        
//         if(tl==tr){
//             mask[v]=(1LL<<(c-'a'));
//             return;
//         }
        
//         ll m=(tl+tr)/2;
//         if(l<=m) update(2*v,tl,m,l,c);
//         else update(2*v+1,m+1,tr,l,c);
        
//         pull(v);
        
        
//     }
    
//     void update(ll l,char c){
//         update(1,0,n-1,l,c);
//     }
    
//     ll getMask(ll v,ll tl,ll tr,ll l,ll r){
        
//         if(r<tl||l>tr) return 0;
//         if(l<=tl&&tr<=r) return mask[v];
        
//         ll m=(tl+tr)/2;
//         return getMask(2*v,tl,m,l,r)|getMask(2*v+1,m+1,tr,l,r);
        
        
//     }
    
//     ll getMask(ll l,ll r){
//         return getMask(1,0,n-1,l,r);
//     }
    
    
// };


template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) { //arguements : 1 - number of levels, V - the array
		for (ll pw = 1, k = 1; pw * 2 <= len(V); pw *= 2, ++k) {
			jmp.emplace_back(len(V) - pw * 2 + 1);
			fls(j,0,len(jmp[k]) - 1)
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(ll a, ll b) { //// query for minimum on llerval [a, b)
		assert(a < b); // or return inf if a == b
		ll dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};


struct LCA {
	ll T = 0;
	vl time, path, ret, depth;
	RMQ<ll> rmq;
	LCA(vector<vl>& C) : time(len(C)), rmq((dfs(C,0,-1), ret)), depth(len(C)) {}
	void dfs(vector<vl>& C, ll v, ll par) {
		time[v] = T++;
		for (ll y : C[v]) if (y != par) {
			path.push_back(v), ret.push_back(time[v]);
            depth[y] = depth[v] + 1;
			dfs(C, y, v);
		}
	}

	ll lca(ll a, ll b) {
		if (a == b) return a;
		tie(a, b) = minmax(time[a], time[b]);
		return path[rmq.query(a, b)];
	}
	ll dist(ll a, ll b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};


void solve(){
    
    
    
    
    
    
    
    
    
    return;
}


int main() {
    fastio;
    
    // freopen("robots.in", "r", stdin);
    // freopen("out.out", "w", stdout);
    
    // sieve();
    // factf();
    // phif();
    
    
    
    
    ll z=0;
    
    
    // solve();
    // return 0;
 
    test{
 
        // z++;
        // cout << "Case " << z << ": ";
        solve();
 
 
    }
 
 
    return 0;
}