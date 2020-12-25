#include <bits/stdc++.h>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ldb;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll start, n; 
bool ispr[1111111]; 
// ispr[i] : if (start + i) is prime or not

bool isprime(ll N) // for test only
{
	if(N==1) return false;
	for(ll i=2 ; i*i<=N ; i++)
		if(N%i==0) return false;
	return true;
}

int main(void)
{
	ll i, j; start = 1e9; n = 20000;
	for(i=1 ; i<=n ; i++) ispr[i]=true;
	for(i=2 ; i*i<=start+n ; i++)
	{
		ll cur=i*((start+i)/i);
		// cur : minimum multiple of i in [start+1, start+n]
		for(j=cur ; j<=start+n ; j+=i)
			if(j!=i) ispr[j-start]=false;
	}
	for(i=1 ; i<=n ; i++) assert(isprime(start + i) == ispr[i]);
	return 0;
}

