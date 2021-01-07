#include <bits/stdc++.h>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ldb;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const ll mod = 1e9 + 7;

// Lucy-Hedgehog Algorithm, O(n^3/4)
// arrays with _0 : count primes
// arrays with _1 : sum primes
// for sum, we will deal everything with (mod 1e9+7)

ll N, C;
bool ispr[333333];
ll num_pr[333333], A_0[333333], B_0[333333];
ll sum_pr[333333], A_1[333333], B_1[333333];

// A keeps 1 ~ sqrt(N)
// B keeps N/1 ~ N/sqrt(N)

// actual dp[x] value (for counting primes)
ll get_0(ll x)
{
	if(x<=C) return A_0[x];
	return B_0[N/x];
}

// actual dp[x] value (for summing primes)
ll get_1(ll x)
{
	if(x<=C) return A_1[x];
	return B_1[N/x];
}

// 1 + 2 + ... + n = n(n+1)/2
ll sum_x(ll n)
{
	n %= mod;
	ll ret = (n * (n + 1)) % mod;
	ret = (ret * (mod + 1) / 2) % mod;
	return ret;
}

void calc_primes(void)
{
	ll i, j;
	for(i=1 ; i<=C ; i++) A_0[i]=i-1;
	for(i=1 ; i<=C ; i++) B_0[i]=N/i-1;
	for(i=1 ; i<=C ; i++) A_1[i]=sum_x(i)-1;
	for(i=1 ; i<=C ; i++) B_1[i]=sum_x(N/i)-1;
	for(i=2 ; i<=C ; i++)
	{
		if(!ispr[i]) continue;
		for(j=1 ; j<=C ; j++)
		{
			if(N/j<i*i) break;
			B_0[j] = B_0[j] - (get_0(N/j/i) - num_pr[i-1]);
			B_1[j] = B_1[j] - (i * (get_1(N/j/i) - sum_pr[i-1] + mod)) % mod;
			if(B_1[j] < 0) B_1[j] += mod;
		}
		for(j=C ; j>=1 ; j--)
		{
			if(j<i*i) break;
			A_0[j] = A_0[j] - (get_0(j/i) - num_pr[i-1]);
			A_1[j] = A_1[j] - (i * (get_1(j/i) - sum_pr[i-1] + mod)) % mod;
			if(A_1[j] < 0) A_1[j] += mod;
		}
	}
}

int main(void)
{ 
	double T = clock(); 
	fio; ll i, j; ispr[1]=false;
	N=1e11; C=(ll)(sqrt(N));
	for(i=2 ; i<=C ; i++) ispr[i]=true;
	for(i=2 ; i<=C ; i++)
	{
		if(!ispr[i]) continue;
		for(j=2*i ; j<=C ; j+=i) ispr[j]=false;
	}
	for(i=2 ; i<=C ; i++)
	{
		num_pr[i]=num_pr[i-1];
		sum_pr[i]=sum_pr[i-1];
		if(!ispr[i]) continue;
		num_pr[i]++; sum_pr[i]+=i;
		if(sum_pr[i]>=mod) sum_pr[i]-=mod;
	}
	calc_primes();
	cout << "Number of primes : " << get_0(N) << "\n";
	cout << "Sum of primes : " << get_1(N) << "\n";
	cout << fixed << setprecision(12) << "Time : " << (clock() - T) / CLOCKS_PER_SEC << "\n";
	return 0;
}

/*

Number of primes : 4118054813
Sum of primes : 475146683
Time : 2.392000000000

*/