#include <bits/stdc++.h>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ldb;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll gcd(ll a, ll b) // inputs should be nonnegative
{
	if(a==0) return b; // a = 0
	if(b==0) return a; // b = 0
	return gcd(b, a%b);
}

int main(void)
{
	cout << gcd(576, 204) << "\n";
}
