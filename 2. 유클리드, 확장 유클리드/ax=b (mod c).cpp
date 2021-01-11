#include <bits/stdc++.h>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ldb;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll gcd(ll a, ll b)
{
	if(a==0) return b; // a = 0
	if(b==0) return a; // b = 0
	return gcd(b, a%b);
}

ll minv(ll a, ll b) // ax == 1 (mod b), assumes gcd(a, b) = 1
{
	if(a==0 && b==1) return 0;
	if(a==1) return 1; // a = 1
	return b - minv(b%a, a) * b / a;
}

void solve(ll a, ll b, ll c) // solve ax == b (mod c), assumes a, c > 0, b >= 0
{
	ll g = gcd(a, c);
	if(b%g!=0)
	{
		cout << "No Solutions" << "\n";
		return;
	}
	a/=g; b/=g; c/=g; // now solve ax == b (mod c)
	ll t = minv(a, c); // at == 1 (mod c)
	ll sol = (t * b) % c; // multiply by b
	cout << "Solution : " << sol << " (mod " << c << ")\n";
}

int main(void)
{
	solve(12, 18, 54);
}
