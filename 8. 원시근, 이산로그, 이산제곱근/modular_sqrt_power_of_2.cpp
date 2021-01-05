#include <bits/stdc++.h>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ldb;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// solve x^2 == a (mod 2^e), a is odd
// we assume e >= 3, since e <= 2 is easy bruteforce
// if x is returned, x, -x, x + 2^{e-1}, -x + 2^{e-1} are solutions
ll modular_sqrt_pow_2(ll a, ll e)
{
	if(a%8!=1) return -1; // no solution
	ll ret = 1;
	// move from x^2 == a (mod 2^i) to x^2 == a (mod 2^{i+1})
	for(ll i=3 ; i<=e-1 ; i++)
	{
		ll stp = (1LL << (i-1));
		if((ret * ret - a) % (1LL << (i + 1)) != 0) ret += stp;
	}
	assert((ret * ret - a) % (1 << e) == 0);
	return ret;

}

int main(void)
{
	cout << modular_sqrt_pow_2(4619761, 25) << "\n";
}