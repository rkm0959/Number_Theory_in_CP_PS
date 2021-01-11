#include <bits/stdc++.h>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ldb;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll gcd(ll a, ll b)
{
	if(a==0) return b;
	if(b==0) return a;
	return gcd(b, a%b);
}

ll minv(ll a, ll b) 
{
	if(a==1) return 1;
	return b - minv(b%a, a) * b / a;
}

// x == A.first (mod A.second)
// x == B.first (mod B.second)
// returns solution as X == ans.first (mod ans.second)
// if no solution, returns (-1, -1)
// always a good idea to keep 0 <= ?.first < ?.second (for ? : A, B, ans)
pair<ll, ll> solve(pair<ll, ll> A, pair<ll, ll> B)
{
	if(A.second == -1 || B.second == -1) return make_pair(-1, -1);
	if(A.second == 1) return B;
	if(B.second == 1) return A;
	ll g = gcd(A.second, B.second); // gcd
	ll l = A.second * (B.second / g); // lcm
	if((B.first-A.first)%g!=0) return make_pair(-1, -1); // no solution case

	ll a = A.second / g; 
	ll b = B.second / g;
	ll mul = (B.first-A.first) / g;
	mul = (mul * minv(a%b, b)) % b; // this is now t
	ll ret = (mul * A.second + A.first); // n_1 t + a_1
	ret %= l; ret = (ret + l) % l; // take modulos
	return make_pair(ret, l);
}

int main(void)
{
	pair<ll, ll> X = solve(make_pair(2, 14), make_pair(9, 21));
	cout << X.first << " " << X.second << "\n";
	pair<ll, ll> Y = solve(make_pair(3, 9), make_pair(7, 12));
	cout << Y.first << " " << Y.second << "\n";
}
