#include <bits/stdc++.h>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ldb;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

bool ispr[1111111];
int mu[1111111];
int C = 1000000; // sieve size

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
}

