#include <bits/stdc++.h>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ldb;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const ll mod = 1e9 + 7;

/*

define a multiplicative function as
f(p) = p, f(p^e) = e(p+1) + 1337 for e >= 2

*/

// we note that for this specific example, sum_pr and precompute are exactly the same array
// for more complex f(p), they will be different 
// for example, there will be more sum_pr arrays, and the contents will be different
ll N, C;
bool ispr[10111111];
int fpr[10111111]; 
int sum_pr[10111111]; // sum of primes
int precompute[10111111]; // sum of f(p)
ll A[10111111]; // for Lucy-Hedgehog step
ll B[10111111]; // for Lucy-Hedgehog step
vector<ll> pr; // prime vector

// true dp value at x
ll getv(ll x)
{
	if(x<=C) return A[x];
	return B[N/x];
}

// 1 + 2 + ... + n
ll sum_x(ll n)
{
	n %= mod;
	ll ret = (n * (n + 1)) % mod;
	ret = (ret * (mod + 1) / 2) % mod;
	return ret;
}

// calculate sum of primes (for F_prime)
void calc_primes(void)
{
	ll i, j;
	for(i=1 ; i<=C ; i++) A[i]=sum_x(i)-1;
	for(i=1 ; i<=C ; i++) B[i]=sum_x(N/i)-1;
	for(i=2 ; i<=C ; i++)
	{
		if(!ispr[i]) continue;
		for(j=1 ; j<=C ; j++)
		{
			if(N/j<i*i) break;
			B[j] = B[j] - (i * (getv(N/j/i) - sum_pr[i-1] + mod)) % mod;
			if(B[j] < 0) B[j] += mod;
		}
		for(j=C ; j>=1 ; j--)
		{
			if(j<i*i) break;
			A[j] = A[j] - (i * (getv(j/i) - sum_pr[i-1] + mod)) % mod;
			if(A[j] < 0) A[j] += mod;
		}
	}
}

// since f(p) = p, we can simply return getv
// if f(p) is a more complex polynomial, 
// we have to run calc_primes to get sum of 1, p, p^2, ... separately
ll F_prime(ll x)
{
	return getv(x);
}

// calculate f(p^e)
ll f(ll p, ll e)
{
	if(e == 1) return p;
	return (e * p + e + 1337) % mod;
}

ll calc_f(ll x)
{
	ll ret=1;
	while(x != 1)
	{
		ll p = fpr[x], e = 0;
		while(x % p == 0) { x /= p; e++; }
		ret = (ret * f(p, e)) % mod;
	}
	return ret;
}

// min_25 sieve
ll min_25(ll m, ll x)
{
	if(x>=pr.size() || m<pr[x]) return 0;
	ll ret=F_prime(m);
	if(x >= 1) ret-=precompute[pr[x-1]];
	if(ret < 0) ret += mod;
	for(ll i=x ; i<pr.size() && pr[i] * pr[i] <=m ; i++)
	{
		ll mul=pr[i]; 
		for(ll j=1 ; ; j++, mul = mul * pr[i])
		{
			if(pr[i]>=m/mul+1) break; 
			ret += f(pr[i], j+1);
			if(ret >= mod) ret -= mod;
			ret += (f(pr[i], j) * min_25(m/mul, i+1)) % mod;
			if(ret >= mod) ret -= mod;
		}
	}
	return ret % mod;
}

int main(void)
{
	fio; ll i, j, ans=0; ispr[1]=false;
	// First, we calculate prefix sum up to 10^7 by simply sieving
	N = 1e7; C = (ll)(sqrt(N));
	for(i=2 ; i<=N ; i++) ispr[i]=true;
	for(i=2 ; i<=N ; i++)
	{
		if(!ispr[i]) continue; fpr[i]=i;
		for(j=2*i ; j<=N ; j+=i)
		{
			if(!fpr[j]) fpr[j]=i;
			ispr[j]=false;
		}
	}
	for(i=1 ; i<=N ; i++) 
	{
		ans += calc_f(i);
		if(ans >= mod) ans -= mod;
	}
	cout << "Answer for 1e7 : " << ans << "\n";

	// Second, we will calculate the same value using min_25 sieve
	memset(ispr, false, sizeof(ispr)); memset(fpr, 0, sizeof(fpr));
	// note : changing all C + 500 to C gives wrong answer!
	for(i=2 ; i<=C+500 ; i++) ispr[i]=true;
	for(i=2 ; i<=C+500 ; i++)
	{
		if(!ispr[i]) continue;
		for(j=2*i ; j<=C+500 ; j+=i) ispr[j]=false;
	}
	for(i=2 ; i<=C+500 ; i++) if(ispr[i]) pr.push_back(i);
	for(i=2 ; i<=C+500 ; i++)
	{
		sum_pr[i]=sum_pr[i-1];
		precompute[i]=precompute[i-1];
		if(!ispr[i]) continue;
		sum_pr[i] += i; if(sum_pr[i] >= mod) sum_pr[i] -= mod;
		precompute[i] += i; if(precompute[i] >= mod) precompute[i] -= mod;
	}
	calc_primes(); // run Lucy-Hedgehog
	cout << "Answer for 1e7 : " << min_25(N, 0) + 1 << "\n";

	// Third, we will calculate prefix sum to 10^14 using min_25 sieve
	memset(ispr, false, sizeof(ispr)); memset(fpr, 0, sizeof(fpr));
	memset(sum_pr, 0, sizeof(sum_pr)); memset(precompute, 0, sizeof(precompute));
	memset(A, 0, sizeof(A)); memset(B, 0, sizeof(B)); pr.clear();
	N = 1e14; C = 1e7;
	for(i=2 ; i<=C+500 ; i++) ispr[i]=true;
	for(i=2 ; i<=C+500 ; i++)
	{
		if(!ispr[i]) continue;
		for(j=2*i ; j<=C+500 ; j+=i) ispr[j]=false;
	}
	for(i=2 ; i<=C+500 ; i++) if(ispr[i]) pr.push_back(i);
	for(i=2 ; i<=C+500 ; i++)
	{
		sum_pr[i]=sum_pr[i-1];
		precompute[i]=precompute[i-1];
		if(!ispr[i]) continue;
		sum_pr[i] += i; if(sum_pr[i] >= mod) sum_pr[i] -= mod;
		precompute[i] += i; if(precompute[i] >= mod) precompute[i] -= mod;
	}

	double T = clock();
	calc_primes(); 
	cout << fixed << setprecision(12) << "Lucy-Hedgehog Step : " << (clock() - T) / CLOCKS_PER_SEC << " seconds!\n";
	double TT = clock();
	cout << "Answer for 1e14 : " << min_25(N, 0) + 1 << "\n";
	cout << fixed << setprecision(12) << "Min_25 Step : " << (clock() - TT) / CLOCKS_PER_SEC << " seconds!\n";

	return 0;
}

/*

Answer for 1e7 : 479672866
Answer for 1e7 : 479672866
Lucy-Hedgehog Step : 327.372000000000 seconds!
Answer for 1e14 : 884267024
Min_25 Step : 424.646000000000 seconds!

for N = 1e14, this is quite fast :)

*/