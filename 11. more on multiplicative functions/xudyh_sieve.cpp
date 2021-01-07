#include <bits/stdc++.h>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ldb;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const ll mod = 1e9 + 7;

ll mem[11111], C, n; // select C ~ n^(2/3), O(n^2/3) algorithm
ll prefix_f[1111111]; // prefix sum of f precomputed
ll phi[1111111];

// make sure to reset array mem appropriately
// NOTE : one run of getval(n) calculates ALL prefix sums for floor(n/i) values

// for f = phi, we select g = 1 and (f * g)(x) = x
ll prefix_g(ll x) // prefix sum of g, easily computed
{
	return x % mod;
}

ll prefix_conv(ll x) // prefix sum of (f * g), easily computed
{
	x %= mod;
	ll ret = (x * (x + 1)) % mod;
	ret = (ret * (mod + 1) / 2) % mod;
	return ret;
}

ll getval(ll x) // get prefix sum of f
{
	if(x<=C) return prefix_f[x]; // prefix sum precomputed
	if(mem[n/x]!=0) return mem[n/x]; // trick - use n/x as the index to [not use map/unordered_map] 
	ll ret=0, add;
	for(ll i=2, la ; i<=x ; i=la+1)
	{
		la = x/(x/i);
		add = prefix_g(la) - prefix_g(i-1);
		if(add < 0) add += mod;
		add = (add * getval(x/i)) % mod;
		ret += add; if(ret >= mod) ret -= mod;
	}
	ret = prefix_conv(x) - ret;
	if(ret<0) ret += mod;
	return mem[n/x]=ret;
}

int main(void)
{
	fio; ll i, j; n = 1e9; C = 1e6;
	for(i=1 ; i<=C ; i++) phi[i]=i;
	for(i=1 ; i<=C ; i++)
		for(j=2*i ; j<=C ; j+=i) phi[j]-=phi[i];
	// precompute prefix_f
	for(i=1 ; i<=C ; i++) 
	{
		prefix_f[i]=prefix_f[i-1]+phi[i];
		if(prefix_f[i]>=mod) prefix_f[i]-=mod;
	}
	cout << getval(n) << "\n";
	return 0;
}
