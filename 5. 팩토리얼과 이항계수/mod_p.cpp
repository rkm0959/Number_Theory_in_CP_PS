#include <bits/stdc++.h>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ldb;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// we assume p is a prime

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

ll n, p;
ll inv[1111111]; // modular inverse of i
ll fac[1111111]; // factorial of i
ll invfac[1111111]; // modular inverse of fac[i]

// we assume n < p here
void topic_2_method_1(void)
{
	fac[0]=1; invfac[0]=1; 
	for(ll i=1 ; i<=n ; i++) 
	{
		fac[i]=(fac[i-1]*i)%p;
		invfac[i]=minv(fac[i], p);
	}
}

// we assume n < p here
void topic_2_method_2(void)
{
	fac[0]=fac[1]=1; invfac[0]=invfac[1]=1; inv[1]=1;
	for(ll i=2 ; i<=n ; i++)
	{
		fac[i]=(fac[i-1]*i)%p;
		inv[i]=((p-p/i)*inv[p%i])%p;
		invfac[i]=(invfac[i-1]*inv[i])%p;
	}
}

// we assume n < p here
void topic_2_method_3(void)
{
	fac[0]=1; invfac[0]=1;
	for(ll i=1 ; i<=n ; i++) fac[i]=(fac[i-1]*i)%p;
	invfac[n]=minv(fac[n], p);
	for(ll i=n-1 ; i>=1 ; i--) invfac[i]=(invfac[i+1]*(i+1))%p;
	for(ll i=1 ; i<=n ; i++) inv[i]=(fac[i-1]*invfac[i])%p;	
}

// returns (e, m mod p) where n! = p^e m 
// to use this function, we assume that we have precomputed the arrays fac, invfac for 0 <= i < p
pair<ll, ll> factorial_p(ll n)
{
	if(n<p) return make_pair(0, fac[n]); 
	ll k = n/p; ll r = n%p;
	pair<ll, ll> val = factorial_p(k);
	ll e = val.first + k;
	ll m = val.second;
	m = (m * exp(fac[p-1], k, p)) % p; // note : fac[p-1] == -1 (mod p)
	// therefore, to save time, we can do m = (k % 2 == 0 ? m : (p-m)); instead
	m = (m * fac[r]) % p;
	return make_pair(e, m);
}

ll ncr_case_1(ll n, ll k)
{
	if(k>n-k) k=n-k; ll ret=1;
	for(ll i=1 ; i<=k ; i++)
	{
		ret=(ret*(n-i+1))%p;
		ret=(ret*minv(i, p))%p; 
		// or, ret = (ret * inv[i]) % p if inv is computed
	}
	return ret;
}

// fac, invfac is computed, and n, k < p
ll ncr_simple(ll n, ll k)
{
	if(n<0 || k<0 || n<k) return 0;
	ll ret=fac[n];
	ret=(ret*invfac[k])%p;
	ret=(ret*invfac[n-k])%p;
	return ret;
}

// fac, invfac is computed
ll ncr_case_3_method_1(ll n, ll k)
{
	if(n<0 || k<0 || n<k) return 0;
	if(n<p && k<p) return ncr_simple(n, k);
	ll n_0 = n % p; ll k_0 = k % p;
	ll ret = ncr_case_3_method_1(n / p, k / p);
	ret = (ret * ncr_simple(n_0, k_0)) % p;
	return ret;
}

// fac, invfac is computed
ll ncr_case_3_method_2(ll n, ll k)
{
	if(n<0 || k<0 || n<k) return 0;
	pair<ll, ll> V1 = factorial_p(n);
	pair<ll, ll> V2 = factorial_p(k);
	pair<ll, ll> V3 = factorial_p(n-k);
	ll e = V1.first - V2.first - V3.first;
	ll m = V1.second;
	m = (m * inv[V2.second]) % p;
	m = (m * inv[V3.second]) % p;
	if(e >= 1) return 0;
	return m;
}
