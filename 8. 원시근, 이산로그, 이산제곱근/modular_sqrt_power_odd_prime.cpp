#include <bits/stdc++.h>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ldb;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll minv(ll a, ll b) 
{
	if(a==1) return 1;
	return b - minv(b%a, a) * b / a;
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

// tonelli-shanks, quite dirty code...
ll tonelli_shanks(ll a, ll p) // x^2 == a (mod p)
{
	ll Q, S=0, tp=p, cc=p-1, z, sx=0, tem;
	if(a==0) return 0;
	if(exp(a, (p-1)/2, p) != 1) return -1; // no solution
	if(p%4 == 3) return exp(a, (p+1)/4, p);
	while(cc%2==0) S++, cc/=2; Q=cc;
	for(z=2 ; ; z++) if(exp(z, (p-1)/2, p)!=1) break;
	ll M=S, c=exp(z,Q,p), t=exp(a,Q,p), R=exp(a,(Q+1)/2,p);
	while(1)
	{
		if(t==0) return 0;
		if(t==1) return R%p;
		sx=0; tem=t;
		while(1)
		{
			sx++; tem=(tem*tem)%p;
			if(tem==1) break;
		}
		ll b=exp(c, 1LL<<(M-sx-1), p);
		M=sx; c=(b*b)%p; t=(t*c)%p; R=(R*b)%p;
	}
}

// we assume p is odd prime, gcd(a, p) = 1
ll modular_sqrt_power_odd(ll a, ll p, ll e)
{
	ll r = tonelli_shanks(a, p);
	if(r==-1) return -1;
	ll cur = p;
	// x^2 == a (mod p^i) to x^2 == a (mod p^{i+1})
	for(ll i=1 ; i<=e-1 ; i++)
	{
		ll val_1 = (2 * r) % p;
		ll val_2 = (a - r * r) / cur;
		val_2 = (val_2 % p);
		if(val_2 < 0) val_2 += p;
		ll t = (val_2 * minv(val_1, p)) % p;
		r += t * cur; cur = cur * p;
	}
	return r;
}

int main(void)
{
	ll res = 37587681; ll p_1 = 998244353;
	ll t_1 = tonelli_shanks((res * res) % p_1, p_1);
	cout << t_1 << " " << p_1 - t_1 << "\n";

	ll p_2 = 1327; ll n = p_2 * p_2 * p_2;
	ll t_2 = modular_sqrt_power_odd((res * res) % n, p_2, 3);
	cout << t_2 << " " << n - t_2 << "\n";

	return 0;
}