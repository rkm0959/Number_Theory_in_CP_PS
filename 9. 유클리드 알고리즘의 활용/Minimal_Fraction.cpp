#include <bits/stdc++.h>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ldb;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// we assume that A/B < X/Y, gcd(A, B) = 1, gcd(X, Y) = 1
// we also assume that A, X, Y >= 0, B >= 1

// A/B < ?/? < X/Y
pair<ll, ll> construct(ll A, ll B, ll X, ll Y)
{
	if(A==0) return make_pair(1, Y/X+1);
	if(Y==0 || A/B+1<X/Y || (A/B+1==X/Y && X%Y!=0)) return make_pair(A/B+1, 1);
	if(A/B+1==X/Y && X%Y==0)
	{
		ll D=B/((X/Y)*B-A)+1;
		return make_pair((A*D)/B+1, D);
	}
	pair<ll, ll> TT=construct(Y, X%Y, B, A%B);
	return make_pair(TT.second + (A/B) * TT.first, TT.first);
}