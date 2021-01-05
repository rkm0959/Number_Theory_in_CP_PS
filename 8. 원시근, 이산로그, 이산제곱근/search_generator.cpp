#include <bits/stdc++.h>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ldb;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// for n = 2, 4 : 3 is a generator of both
// now assume n = p^e and we will search a generator of n
// we need factorization of p-1, and here we'll use O(sqrt(p)) factorization
// if p is very large, simply use Pollard-Rho for factorization

vector<ll> pr; 

void factorize(ll n)
{
	for(ll i=2 ; i*i<=n ; i++)
	{
		if(n%i==0)
		{
			pr.push_back(i);
			while(n%i==0) n/=i;
		}
	}
	if(n!=1) pr.push_back(n);
}

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

ll order(ll g, ll n, ll phi_n)
{
	ll ord=phi_n;
	for(ll i=0 ; i<pr.size() ; i++)
		while(ord%pr[i]==0 && exp(g, ord/pr[i], n)==1) ord/=pr[i];
	return ord;
}

// p : odd prime, e >= 1
// searches generator of p^e
// n = p^e, phi_n = p^{e-1}(p-1)
ll get_generator(ll p, ll e)
{
	ll n=1, phi_n, ord; pr.clear(); 
	for(ll i=1 ; i<=e ; i++) n=n*p;
	phi_n=n-n/p; factorize(p-1);
	if(e>=2) pr.push_back(p);
	for(ll g=2 ; ; g++)
	{
		if(g==0 || g==1) continue;
		if(order(g, n, phi_n)==phi_n) return g;
	}
}

int main(void)
{
	cout << get_generator(998244353, 1) << "\n";
	cout << get_generator(17, 6) << "\n";
}