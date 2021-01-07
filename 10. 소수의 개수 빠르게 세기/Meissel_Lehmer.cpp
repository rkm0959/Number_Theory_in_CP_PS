#include <bits/stdc++.h>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ldb;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// there can *definitely* be some more optimization here : left to reader
// also, refer to the editorial of Codeforces' "Four Divisors" (Editorial)
// Editorial uses a = pi(x^1/2) to completely remove P_2 from the equation
// this code is strictly for a showcase of concept & understanding

int C = 5000000; // > 10^(20/3)
ll N = 10000000000LL; // 10^10

vector<int> Query[1000];
map< pair<ll, ll>, ll> M; // computed values of phi(x, a)
set< pair<ll, ll> > vis;
vector<int> pr;
ll ans; 
bool ispr[5000001]; // sieve
int cnt_pr[5000001]; // pi(x) precompute
int alive[5000001]; // for offline queries

struct Fenwick
{
	int tree[2 * 5000005];
	void update(int x, int v) { while(x<=C) { tree[x]+=v; x+=(x&-x); } }
	int query(int x) { int ret=0; while(x) { ret+=tree[x]; x-=(x&-x); } return ret; }
} T;

ll P_2(ll n, ll a)
{
	ll ret = 0;
	for(ll i = a+1 ; i < pr.size() && pr[i] * pr[i] <= n ; i++)
		ret += cnt_pr[n/pr[i]]- (i - 1);
	return ret;
}

void top_down_prep(ll n, ll a)
{
	if(vis.count(make_pair(n, a))) return;
	vis.insert(make_pair(n, a));
	if(a == 0) return;
	if(n <= C)
	{
		Query[a].push_back(n);
		return;
	}
	top_down_prep(n, a-1);
	top_down_prep(n/pr[a], a-1);
}

ll top_down_calc(ll n, ll a)
{
	if(M.find(make_pair(n, a))!=M.end()) return M[make_pair(n, a)];
	if(a==0) return n;
	return M[make_pair(n, a)] = top_down_calc(n, a-1) - top_down_calc(n/pr[a], a-1);
}

int main(void)
{
	double TT = clock();
	fio; ll i, j; ispr[1]=false;
	for(i=2 ; i<=C ; i++) ispr[i]=true;
	for(i=2 ; i<=C ; i++)
	{
		if(!ispr[i]) continue;
		for(j=2*i ; j<=C ; j+=i) ispr[j]=false;
	}
	for(i=2 ; i<=C ; i++)
	{
		cnt_pr[i]=cnt_pr[i-1];
		if(ispr[i]) cnt_pr[i]++;
	}
	pr.push_back(0); // for 1-indexing
	for(i=2 ; i*i<=N ; i++)
	{
		if(!ispr[i]) continue;
		pr.push_back(i);
	}
	ll a = cnt_pr[2155]; // 2155 ~ 10^(10/3)
	ans += a - 1 - P_2(N, a);
	top_down_prep(N, a); // preparation for offline query
	for(i=1 ; i<=C ; i++) alive[i]=1; 
	for(i=1 ; i<=C ; i++) T.update(i, 1); // obviously bad, you can do this in O(C)
	for(i=1 ; i<=a ; i++)
	{
		sort(Query[i].begin(), Query[i].end());
		Query[i].erase(unique(Query[i].begin(), Query[i].end()), Query[i].end());
	}
	for(i=1 ; i<=a ; i++)
	{
		for(j=pr[i] ; j<=C ; j+=pr[i])
			if(alive[j]) T.update(j, -1), alive[j]=0;
		for(j=0 ; j<Query[i].size() ; j++)
			M[make_pair(Query[i][j], i)] = T.query(Query[i][j]);
	}
	ans += top_down_calc(N, a);
	cout << "Number of primes <= 10^10 is : " << ans << "\n";
	cout << fixed << setprecision(12) << (clock() - TT) / CLOCKS_PER_SEC << "\n";
	return 0;
}

/*

Number of primes <= 10^10 is : 455052511
0.482000000000

quite fast, even with a quite unoptimized implementation!

*/