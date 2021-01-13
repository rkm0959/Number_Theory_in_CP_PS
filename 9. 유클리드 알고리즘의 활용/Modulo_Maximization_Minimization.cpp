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

// binary search + Linear Inequality with Modulo
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

// rq (mod m) min for 1 <= q <= c
ll min_rem_bs(ll r, ll m, ll c)
{
	r = r % m;
	if(c < 1) return 1e18; // failure
	if(r == 0) return 0;
	ll cyc = m / gcd(m, r);
	if(c >= cyc) return 0;
	ll lef = 1, rig = m-1, mid, best;
	while(lef <= rig)
	{
		mid = (lef + rig) >> 1;
		if(sol_ex(r, m, 1, mid) && solve(r, m, 1, mid) <= c) best = mid, rig = mid - 1;
		else lef = mid + 1;
	}
	return best;
}

// rq (mod m) max for 1 <= q <= c
ll max_rem_bs(ll r, ll m, ll c)
{
	r = r % m;
	if(r == 0 || c <= m / r) return r * c;
	ll cyc = m / gcd(m, r);
	if(c >= cyc) return m - gcd(m, r);
	return m - min_rem_bs(m-r, m, c);
}

ll min_rem_brute(ll r, ll m, ll c)
{
	ll ret = m;
	for(ll i=1 ; i<=c ; i++) ret = min(ret, (r * i) % m);
	return ret;
}

ll max_rem_brute(ll r, ll m, ll c)
{
	ll ret = 0;
	for(ll i=1 ; i<=c ; i++) ret = max(ret, (r * i) % m);
	return ret;
}

int main(void)
{
	ll it = 300000;
	while(it--)
	{
		ll m = rng() % 100000000 + 100000;
		ll r = rng() % 100000000 + 100000;
		ll c = rng() % 100000 + 10000;
		ll res_1 = min_rem_bs(r, m, c);
		ll res_2 = min_rem_brute(r, m, c);
		ll res_3 = max_rem_bs(r, m, c);
		ll res_4 = max_rem_brute(r, m, c);
		assert(res_1 == res_2 && res_3 == res_4);
	}
	return 0;
}
