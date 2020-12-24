#include <bits/stdc++.h>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ldb;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll mod=1e9+7;

int main(void)
{
	int n=45; int i, la, ans=0;
	for(i=1 ; i<=n ; i=la+1) // works in O(sqrt(n))
	{
		la=n/(n/i);
		cout << "From " << i << " to " << la << " floor(n/i) = " << n/i << "\n";
	}

	// Exercise : find sum_{i=1}^n floor(n/i) in O(sqrt(n)) time
	for(i=1, ans=0 ; i<=n ; i=la+1)
	{
		la=n/(n/i);
		ans+=(la-i+1)*(n/i);
	}
	cout << ans << "\n";
	for(i=1, ans=0 ; i<=n ; i++) ans+=n/i;
	cout << ans << "\n";
	return 0;
}