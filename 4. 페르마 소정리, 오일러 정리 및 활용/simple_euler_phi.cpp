#include <bits/stdc++.h>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ldb;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

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

