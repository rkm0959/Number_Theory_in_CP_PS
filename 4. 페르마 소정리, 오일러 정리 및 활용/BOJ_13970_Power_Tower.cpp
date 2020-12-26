#include <bits/stdc++.h>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ldb;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// for BOJ 13970, we can achieve speedup by precomputing all phi function values

ll exp(ll x, ll y, ll mod)
{
	ll ret=1;
	while(y)
	{
		if(y&1) ret=(ret*x)%mod, y--;
		x=(x*x)%mod; y>>=1;
	}
	return ret;
}

// simply calculate x ** y, without mods
ll power(ll x, ll y)
{ 
	ll ret=1;
	while(y)
	{
		if(y&1) ret=ret*x, y--;
		x=x*x; y>>=1;
	}
	return ret;
}

ll phi(ll n)
{
	ll i; ll ret=n;
	for(i=2 ; i*i<=n ; i++)
	{
		if(n%i==0)
		{
			ret-=ret/i;
			while(n%i==0) n/=i;
		}
	}
	if(n!=1) ret-=ret/n;
	return ret;
}

ll constrain_exp(ll x, ll y)
{
	if(x==1 || y==0) return 1;
	if(x>=2 && y>=7) return 100;
	if(x>=3 && y>=5) return 100;
	if(x>=4 && y>=4) return 100;
	if(x>=5 && y>=3) return 100;
	if(x>=10 && y>=2) return 100;
	if(x>=100 && y>=1) return 100;
	return power(x, y);
}

ll x[1111111], n, m;

ll check_large(ll st) // THIS IS O(1)
{
	if(n-st+1>=4) return 100; // there are at least four numbers
	if(st==n) return x[n];
	// iteratively calculate, but cap the value at 100
	ll val = constrain_exp(x[n-1], x[n]);
	for(int i=n-2 ; i>=st ; i--) val = constrain_exp(x[i], val);
	return val;
}

ll calc(ll cur, ll mod)
{
	if(mod==1) return 0;
	if(cur==n) return x[n]%mod;
	// start to reduce problem
	// check [x[cur+1], ... , x[n]] is large
	ll cases = check_large(cur+1);
	if(cases >= 100)
	{
		ll next_mod = phi(mod);
		ll exponent = calc(cur+1, next_mod);
		return exp(x[cur], exponent + 100 * next_mod, mod);
	}
	else
	{
		ll next_mod = phi(mod);
		ll exponent = cases;
		return exp(x[cur], exponent, mod);
	}
}

void solve(void)
{
	cin>>n;
	for(int i=1 ; i<=n ; i++) cin>>x[i];
	// remove all 1s and the numbers after it
	for(int i=n ; i>=1 ; i--) if(x[i]==1) n=i-1;
	cout << (n == 0 ? 1 : calc(1, m)) << "\n";
}

int main(void)
{
	fio; int tc; cin>>tc>>m;
	while(tc--) solve();
}