#include <bits/stdc++.h>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ldb;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

bool isprime(ll n)
{
	if(n==1) return false;
	for(ll i=2 ; i*i<=n ; i++)
		if(n%i==0) return false;
	return true;
}

ll cnt_factor(ll n)
{
	ll ret=0;
	for(ll i=1 ; i*i<=n ; i++)
	{
		if(n%i==0)
		{
			if(i*i==n) ret+=1;
			else ret+=2;
			// if you want all factors, add i, n/i (only one of them if i*i==n)
		}
	}
	return ret;
}

vector< pair<ll, ll> > factorize(ll n)
{
	vector< pair<ll, ll> > ret; ret.clear();
	for(ll i=2 ; i*i<=n ; i++)
	{
		if(n%i==0)
		{
			ll cnt=0;
			while(n%i==0) { cnt++; n/=i; }
			ret.push_back(make_pair(i, cnt));
		}
	}
	if(n!=1) ret.push_back(make_pair(n, 1));
	return ret;
}

int main(void)
{
	cout << isprime(10007) << "\n";
	cout << cnt_factor(8148) << "\n";
	vector< pair<ll, ll> > test = factorize(8148);
	for(pair<ll, ll> entry : test) cout << entry.first << " " << entry.second << "\n";
}