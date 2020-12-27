#include <bits/stdc++.h>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ldb;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

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

bool ispr[1111111];
int fpr[1111111];
int C = 1000000; 
int pr_cnt[1111111];

ll mod = 1769817825; // we do not need factorization or any conditions on mod

void factorize(int n, int v) // v == 1 -> numerator, v == -1 -> denominator
{
	while(n!=1)
	{
		int p = fpr[n];
		while(n%p==0)
		{
			pr_cnt[p]+=v;
			n/=p;
		}
	}
}

ll calc_ncr(int n, int k)
{
	if(n<0 || k<0 || n<k) return 0;
	ll ret=1;
	if(k>n-k) k=n-k;
	for(int i=n-k+1 ; i<=n ; i++) factorize(i, 1);
	for(int i=1 ; i<=k ; i++) factorize(i, -1);
	for(int i=1 ; i<=n ; i++)
	{
		if(!ispr[i] || !pr_cnt[i]) continue;
		ret = (ret * exp(i, pr_cnt[i], mod)) % mod;
	}
	return ret;
}

int main(void)
{
	int i, j; ispr[1]=false; fpr[1]=1;
	for(i=2 ; i<=C ; i++) ispr[i]=true;
	for(i=2 ; i<=C ; i++)
	{
		if(!ispr[i]) continue; fpr[i]=i; 
		for(j=2*i ; j<=C ; j+=i) 
		{
			ispr[j]=false;
			if(!fpr[j]) fpr[j]=i; 
		}
	}
	int n = 678572; int k = 134865;
	cout << calc_ncr(n, k) << "\n";
	return 0;
}


