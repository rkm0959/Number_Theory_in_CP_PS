#include <bits/stdc++.h>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ldb;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// take modulos if you want/need

// 1 : naive
// 2 : after double count
// 3 : sqrt technique with n/i-type values

ll cnt_factor(ll n)
{
	ll ret=0;
	for(ll i=1 ; i*i<=n ; i++)
	{
		if(n%i==0)
		{
			if(i*i==n) ret+=1;
			else ret+=2;
		}
	}
	return ret;
}

ll sum_factor(ll n)
{
	ll ret=0;
	for(ll i=1 ; i*i<=n ; i++)
	{
		if(n%i==0)
		{
			if(i*i==n) ret+=i;
			else ret+=i+n/i;
		}
	}
	return ret;
}

ll sum_tau_1(ll n)
{
	ll ret=0;
	for(ll i=1 ; i<=n ; i++) 
		ret+=cnt_factor(i);
	return ret;
}

ll sum_tau_2(ll n)
{
	ll ret=0;
	for(ll i=1 ; i<=n ; i++)
		ret+=n/i;
	return ret;
}

ll sum_tau_3(ll n)
{
	ll ret=0;
	for(ll i=1, la ; i<=n ; i=la+1)
	{
		la=n/(n/i); // (n/i), (n/(i+1)), ... , (n/la) are all the same values
		ret += (la-i+1) * (n/i); // there are la - i + 1 values equal to (n/i)
	}
	return ret;
}

ll sum_sig_1(ll n)
{
	ll ret=0;
	for(ll i=1 ; i<=n ; i++)
		ret+=sum_factor(i);
	return ret;
}

ll sum_sig_2(ll n)
{
	ll ret=0;
	for(ll i=1 ; i<=n ; i++)
		ret+=i*(n/i);
	return ret;
}

ll sum_i(ll x) // 1 + 2 + ... + x
{
	return x*(x+1)/2; 
}

ll sum_sig_3(ll n)
{
	ll ret=0;
	for(ll i=1, la ; i<=n ; i=la+1)
	{
		la=n/(n/i); // (n/i), (n/(i+1)), ... , (n/la) are all the same values
		ret += (sum_i(la)-sum_i(i-1)) * (n/i); // add (i + (i+1) + ... + la) * (n/i)
	}
	return ret;
}

int main(void)
{
	cout << sum_tau_1(10000) << "\n";
	cout << sum_tau_2(10000) << "\n";
	cout << sum_tau_3(10000) << "\n";

	cout << sum_sig_1(10000) << "\n";
	cout << sum_sig_2(10000) << "\n";
	cout << sum_sig_3(10000) << "\n";

	return 0;
}