#include <bits/stdc++.h>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ldb;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// we assume p is a prime
// we work with modulus mod = p^ex

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

ll minv(ll a, ll b) 
{
	if(a==1) return 1;
	return b - minv(b%a, a) * b / a;
}

ll n, p, ex, mod; // mod = p^ex
ll inv[1111111]; // modular inverse of i
ll fac[1111111]; // factorial of i
ll invfac[1111111]; // modular inverse of fac[i]
ll val[1111111]; // val[i] from topic 3

// we assume n < p here
void topic_2_method_1(void)
{
	fac[0]=1; invfac[0]=1; 
	for(ll i=1 ; i<=n ; i++) 
	{
		fac[i]=(fac[i-1]*i)%mod;
		invfac[i]=minv(fac[i], mod);
	}
}

// we assume n < p here
void topic_2_method_3(void)
{
	fac[0]=1; invfac[0]=1;
	for(ll i=1 ; i<=n ; i++) fac[i]=(fac[i-1]*i)%mod;
	invfac[n]=minv(fac[n], mod);
	for(ll i=n-1 ; i>=1 ; i--) invfac[i]=(invfac[i+1]*(i+1))%mod;
	for(ll i=1 ; i<=n ; i++) inv[i]=(fac[i-1]*invfac[i])%mod;	
}

// precompute val for topic 3
void topic_3_precompute(void)
{
	val[0]=1;
	for(ll i=1 ; i<=mod-1 ; i++)
	{
		if(i%p==0) val[i]=val[i-1];
		else val[i]=(val[i-1]*i)%mod;
	}
}

// returns (e, m mod p^ex) where n! = p^e m 
// to use this function, we assume that we have precomputed the arrays val for 0 <= i < p^ex
pair<ll, ll> factorial_p(ll n)
{
	if(n<p) return make_pair(0, val[n]);  
	ll k = n/p; 
	pair<ll, ll> V = factorial_p(k);
	ll e = V.first + k;
	ll kp = n/mod; ll rp = n%mod;
	ll m = V.second;
	// to achieve speedup, use kp % 2 instead of kp
	m = (m * exp(val[mod-1], kp, mod)) % mod;
	m = (m * val[rp]) % mod;
	return make_pair(e, m);
}

// k < p required
ll ncr_case_1(ll n, ll k)
{
	if(k>n-k) k=n-k; ll ret=1;
	for(ll i=1 ; i<=k ; i++)
	{
		ret=(ret*(n-i+1))%mod;
		ret=(ret*minv(i, mod))%mod; 
		// or, ret = (ret * inv[i]) % mod if inv is computed
	}
	return ret;
}

// val is computed
ll ncr_case_3_method_2(ll n, ll k)
{
	if(n<0 || k<0 || n<k) return 0;
	pair<ll, ll> V1 = factorial_p(n);
	pair<ll, ll> V2 = factorial_p(k);
	pair<ll, ll> V3 = factorial_p(n-k);
	ll e = V1.first - V2.first - V3.first;
	ll m = V1.second;
	m = (m * minv(V2.second, mod)) % mod;
	m = (m * minv(V3.second, mod)) % mod;
	if(e >= ex) return 0;
	for(ll i=1 ; i<=e ; i++) m = (m * p) % mod;
	return m;
}