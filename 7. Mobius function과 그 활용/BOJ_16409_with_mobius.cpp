#include <bits/stdc++.h>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ldb;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

bool ispr[11111111];
int mu[11111111];
int C = 10000000; // sieve size

// this is quite slow compared to other sols on BOJ
// to optimize, learn linear sieve (optional)

int main(void)
{
	int i, j; ispr[1]=false; mu[1]=1;
	for(i=2 ; i<=C ; i++) ispr[i]=true, mu[i]=1;
	for(i=2 ; i<=C ; i++)
	{
		if(!ispr[i]) continue; mu[i]=-1; // now i is a prime
		for(j=2*i ; j<=C ; j+=i) // iterate over all multiples  
		{
			ispr[j]=false;
			mu[j]=-mu[j]; // new prime i
			if((j/i)%i==0) mu[j]=0; // i * i is a divisor of j
		}
	}
	ll ans=0, a, b, c, d; 
	cin>>a>>b>>c>>d;
	for(i=1 ; i<=min(b, d) ; i++) 
		ans+=mu[i]*(b/i-(a-1)/i)*(d/i-(c-1)/i);
	cout<<ans; return 0;
}

