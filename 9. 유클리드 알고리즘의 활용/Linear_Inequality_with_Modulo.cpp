#include <bits/stdc++.h>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ldb;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll ceil(ll n, ll m) { return (n+m-1)/m; }

ll gcd(ll a, ll b)
{
	if(a==0) return b;
	if(b==0) return a;
	return gcd(b, a%b);
}

// we assume solution exists
ll solve(ll A, ll M, ll L, ll R)
{
	if(L == 0 || L > R) return 0;
	if(2 * A > M) { swap(L, R); A = M - A; L = M - L; R = M - R; }
	ll val_1 = ceil(L, A);
	if(A * val_1 <= R) return val_1;
	ll val_2 = solve(A - M % A, A, L % A, R % A);
	return ceil(L + M * val_2, A);
}

bool sol_ex(ll A, ll M, ll L, ll R)
{
	if(L == 0 || L > R) return true;
	ll g = gcd(A, M); 
	if((L-1)/g == R/g) return false;
	return true;
}

ll brute_solve(ll A, ll M, ll L, ll R)
{
	if(L == 0 || L > R) return 0;
	for(ll i=0 ; i<M ; i++)
	{
		ll res = (A * i) % M;
		if(L <= res && res <= R) return i;
	}
	return -1;
}

int main(void)
{
	ll A = 23578235;
	ll M = 787467161;
	ll L = 6786196;
	ll R = 6786926;
	cout << sol_ex(A, M, L, R) << "\n";
	cout << solve(A, M, L, R) << "\n";
	cout << brute_solve(A, M, L, R) << "\n";
	return 0;

}