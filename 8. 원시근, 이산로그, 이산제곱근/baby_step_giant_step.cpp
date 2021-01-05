#include <bits/stdc++.h>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ldb;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// BOJ 4357, but more generalizable
// there can be improvements on this code, leaving that to reader

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

ll minv(ll a, ll b) // ax == 1 (mod b)
{
	if(a==1) return 1; // a = 1
	return b - minv(b%a, a) * b / a;
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

vector<ll> factorize(ll n)
{
	vector<ll> pr; pr.clear();
	for(ll i=2 ; i*i<=n ; i++)
	{
		if(n%i==0)
		{
			pr.push_back(i);
			while(n%i==0) n/=i;
		}
	}
	if(n!=1) pr.push_back(n);
	return pr;
}

ll order(ll g, ll n, ll phi_n)
{
	vector<ll> pr=factorize(phi_n); ll ord=phi_n;
	for(ll i=0 ; i<pr.size() ; i++)
		while(ord%pr[i]==0 && exp(g, ord/pr[i], n)==1) ord/=pr[i];
	return ord;
}

map<ll, ll> M;

ll discrete_log(ll g, ll h, ll ord, ll n)
{
	ll B = (ll)sqrt(ord) + 1;
	ll g_inv = minv(g, n);
	ll cur = h;
	for(ll i=0 ; i<B ; i++)
	{
		M[cur] = i;
		cur = (cur * g_inv) % n;
	}
	ll g_B = exp(g, B, n); cur = 1;
	for(ll i=0 ; i<B ; i++)
	{
		if(M.find(cur)!=M.end()) return (i * B + M[cur]) % ord;
		cur = (cur * g_B) % n;
	}
	return -1;
}

int main(void)
{
	fio; ll g, h, n, phi_n;
	while(cin >> n >> g >> h)
	{
		M.clear();
		phi_n = phi(n);
		ll ord = order(g, n, phi_n);
		ll res = discrete_log(g, h, ord, n);
		if(res == -1) cout << "no solution\n";
		else cout << res << "\n";
	}
	return 0;
}