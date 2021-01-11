#include <bits/stdc++.h>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ldb;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// both functions assume gcd(a, b) = 1 and positive integer inputs

ll minv(ll a, ll b) // ax == 1 (mod b)
{
	if(a==0 && b==1) return 0;
	if(a==1) return 1; // a = 1
	return b - minv(b%a, a) * b / a;
}

pair<ll, ll> solve(ll a, ll b) // solution of ax + by = 1 with 0 <= x < b
{
	if(a==0) return make_pair(0, 1);
	if(b==0) return make_pair(1, 0);
	pair<ll, ll> prv = solve(b, a%b);
	ll x = ((prv.second % b) + b) % b; // x = y' mod b
	ll y = (1 - a * x) / b; // ax + by = 1
	return make_pair(x, y);
}

int main(void)
{
	cout << minv(3, 7) << "\n";
	pair<ll, ll> example = solve(3, 7);
	cout << example.first << " " << example.second << "\n";
}
