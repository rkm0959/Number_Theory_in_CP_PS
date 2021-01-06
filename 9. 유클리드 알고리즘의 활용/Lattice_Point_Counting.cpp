#include <bits/stdc++.h>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ldb;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());


ll get_sum(ll a, ll b) // sum a + (a-b) + ... for positive values
{
	if(a<=0) return 0; ll z=a/b;
	return (z+1)*(2*a-z*b)/2;
}

// x, y > 0, ax + by <= c
ll get_count(ll a, ll b, ll c) 
{
	if(a+b>c) return 0; 
	if(a<b) swap(a, b); 
	ll k=a/b; ll u=(c*k)/a;
	ll ret = get_count(b, a-k*b, c-b*u);
	ret += get_sum(u-k, k);
	return ret;
}

// brute force version of get_count
ll brute_count(ll a, ll b, ll c)
{
	ll ret=0;
	for(ll i=b ; i<=c ; i+=b) ret+=(c-i)/a;
	return ret;
}

// sum floor((a+bk)/c) from k 1 to n
ll summation(ll a, ll b, ll c, ll n)
{
	ll ret=0;
	ret += (a/c) * n; a %= c;
	ret += get_count(b, c, (n + 1) * b + a);
	return ret; 
}

// brute force version of summation
ll brute_summation(ll a, ll b, ll c, ll n)
{
	ll ret=0;
	for(ll i=1 ; i<=n ; i++) ret+=(a+b*i)/c;
	return ret;
}

int main(void)
{
	ll it = 3000; // test
	while(it--)
	{
		ll a = rng() % 10000 + 30;
		ll b = rng() % 10000 + 30;
		ll c = rng() % (ll)(1e9 + 7);
		assert(get_count(a, b, c) == brute_count(a, b, c));

		ll d = rng() % 10000 + 30;
		ll e = rng() % 10000 + 30;
		ll f = rng() % 10000 + 30;
		ll n = rng() % 1000000 + 300;
		assert(summation(d, e, f, n) == brute_summation(d, e, f, n));
	}
	return 0;
}