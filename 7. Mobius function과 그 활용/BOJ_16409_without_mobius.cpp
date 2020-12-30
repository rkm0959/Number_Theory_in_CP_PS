#include <bits/stdc++.h>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ldb;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// NOTE : this gives time-limit-exceeded 
// this is here only for demonstration purposes

ll cnt[11111111];
ll a, b, c, d;

int main(void)
{
	fio; cin>>a>>b>>c>>d; ll T=min(b, d);
	for(ll i=1 ; i<=T ; i++) cnt[i]=(b/i-(a-1)/i)*(d/i-(c-1)/i);
	// cnt[i] : gcd is a multiple of i
	// begin "inclusion-exclusion" process
	for(ll i=T ; i>=1 ; i--)
		for(ll j=2*i ; j<=T ; j+=i) cnt[i]-=cnt[j];
	cout<<cnt[1]; return 0;
}

