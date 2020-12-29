#include <bits/stdc++.h>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ldb;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

bool ispr[1111111];
int fpr[1111111]; // smallest prime divisor
int cnt_pr[1111111]; // number of distinct prime divisor
int phi[1111111]; // euler phi function
int C = 1000000; // sieve size
// ... and much more is possible. ex) mobius function

void quick_factorize(int n) // logarithmic time, after sieve
{
	while(n!=1)
	{
		int p=fpr[n]; n/=p;
		// while(n % p == 0) n /= p; is possible of course
		cout << "Found Prime Divisor " << p << "\n";
		// save these values in a data structure, if needed
	}
}

int main(void)
{
	int i, j; ispr[1]=false; fpr[1]=1; phi[1]=1;
	for(i=2 ; i<=C ; i++) ispr[i]=true, phi[i]=i;
	for(i=2 ; i<=C ; i++)
	{
		if(!ispr[i]) continue; // now i is a prime
		fpr[i]=i; cnt_pr[i]=1; phi[i]=i-1;
		for(j=2*i ; j<=C ; j+=i) // iterate over all multiples  
		{
			ispr[j]=false;
			if(!fpr[j]) fpr[j]=i; 
			cnt_pr[j]++; phi[j]-=phi[j]/i;
		}
	}
	quick_factorize(8148);
}

