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
int expo[1111111]; // expo[p^k] = k
int sum_pr[1111111]; // sum_pr[p^k] = 1 + p + ... + p^k
int tau[1111111]; // number of divisors
int sig[1111111]; // sum of divisors
int C = 1000000; // sieve size


// for reference, O(n log n) from Harmonic Sequence
void easy_tau_sig(void)
{
	for(int i=1 ; i<=C ; i++)
		for(int j=i ; j<=C ; j+=i)
			tau[j]++, sig[j]+=i;
}

// with sieve, O(n log log n)
int main(void)
{
	int i, j; ispr[1]=false; fpr[1]=tau[1]=sig[1]=sum_pr[1]=1; cnt_pr[1]=expo[1]=0;
	for(i=2 ; i<=C ; i++) ispr[i]=true, sig[i]=1, tau[i]=1;
	for(i=2 ; i<=C ; i++)
	{
		if(ispr[i] || cnt_pr[i]==1) // i is a prime power
		{
			if(ispr[i]) fpr[i]=i, cnt_pr[i]=1;
			expo[i]=expo[i/fpr[i]]+1; // expo[p^k] = expo[p^(k-1)] + 1
			sum_pr[i]=sum_pr[i/fpr[i]]+i; // sum_pr[p^k] = sum_pr[p^(k-1)] + p^k
			tau[i]=expo[i]+1; sig[i]=sum_pr[i]; // tau[p^k] = k+1, sig[p^k] = 1 + p + ... + p^k
			for(j=2*i ; j<=C ; j+=i)
			{
				ispr[j]=false;
				if(ispr[i]) cnt_pr[j]++;
				if(!fpr[j] && ispr[i]) fpr[j]=i;
				tau[j]=tau[j]/expo[i]*(expo[i]+1); // p^(k-1) * something -> p^k * something
				sig[j]=sig[j]/sum_pr[i/fpr[i]]*(sum_pr[i]); // p^(k-1) * something -> p^k * something
			}
		} 
	}
	return 0;
}