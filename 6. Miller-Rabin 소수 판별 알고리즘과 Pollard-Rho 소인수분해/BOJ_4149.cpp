#include <bits/stdc++.h>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ldb;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// a lot of code chunks are taken from 
// https://github.com/encrypted-def/BOJ/blob/master/4149.cpp

vector<ll> res;

ll gcd(ll x, ll y)
{
	if(x==0) return y;
	if(y==0) return x;
	return gcd(y, x%y);
}

ll extm(ll x, ll y, ll mod)
{
	__int128 T = x; T *= y;
	return (ll)(T % mod);
}

/*

ll extm(ll x, ll y, ll mod)
{
	ll ret = 0;
	while(y)
	{
		if(y&1) 
		{
			ret+=x; y--;  
			if(ret>=mod) ret-=mod;
		}
		x<<=1; y>>=1;
		if(x>=mod) x-=mod; 
	}
	return ret;
}

*/

ll extexp(ll x, ll y, ll mod)
{
	ll ret=1;
	while(y)
	{
		if(y&1) ret=extm(ret, x, mod), y--;
		x=extm(x, x, mod); y>>=1;
	}
	return ret;
}

bool trial(ll N, ll x)
{
	if(N%x==0) return false;
	ll cnt=-1, d=N-1;
	while(d%2==0) d/=2, cnt++;
	ll p=extexp(x, d, N);
	if(p==1 || p==N-1) return true;
	while(cnt--)
	{
		p=extm(p, p, N);
		if(p==N-1) return true;
	}
	return false;
}

bool is_prime(ll N)
{
	if(N==1) return false;
	ll tc[12]={2,3,5,7,11,13,17,19,23,29,31,37};
	for(int i=0 ; i<12 ; i++)
	{
		if(N==tc[i]) return true;
		if(N>40 && !trial(N,tc[i])) return false;
	}
	if(N<=40) return false;
	return true;
}

ll PollardRho(ll N)
{
	ll x=rng()%(N-2)+2; ll y=x;
	ll c=rng()%(N-1)+1;
	while(1)
	{
		x = extm(x, x, N) + c; if(x >= N) x -= N;
		y = extm(y, y, N) + c; if(y >= N) y -= N;
		y = extm(y, y, N) + c; if(y >= N) y -= N;
		ll d = gcd(abs(x - y), N);
		if(d==1) continue;
		if(!is_prime(d)) return PollardRho(d);
		else return d;
	}
}

void getFactor(ll N)
{
	while(N%2==0) { N/=2; res.push_back(2); }
	while(N!=1 && !is_prime(N))
	{
		ll d=PollardRho(N);
		while(N%d==0) { N/=d; res.push_back(d); }
	}
	if(N!=1) res.push_back(N);
}

int main(void)
{
	fio; ll N; cin>>N; getFactor(N);
	sort(res.begin(), res.end());
	for(int i=0 ; i<res.size() ; i++) cout<<res[i]<<"\n";
	return 0;
}
