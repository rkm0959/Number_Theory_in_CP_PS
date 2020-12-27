#include <bits/stdc++.h>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ldb;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

/*

note : a lot of possible speedups, since modulo is fixed as 142857
ex) hardcoded CRT, arrays instead of vectors, etc..

*/

int exp(int x, int y, int mod)
{
	ll ret=1;
	while(y)
	{
		if(y&1) ret=(1LL*ret*x)%mod, y--;
		x=(1LL*x*x)%mod; y>>=1;
	}
	return ret;
}

int minv(int a, int b) 
{
	if(a==1) return 1;
	return b - (1LL * minv(b%a, a) * b) / a;
}

pair<int, int> solve(pair<int, int> A, pair<int, int> B) // from CRT, but g = 1 is known
{
	int l = A.second * B.second;
	int mul = B.first - A.first;
	mul = (mul % B.second + B.second) % B.second;
	mul = (1LL * mul * minv(A.second, B.second)) % B.second; 
	int ret = (1LL * mul * A.second + A.first) % l; 
	return make_pair(ret, l);
}

vector< vector<int> > factorization; 
vector< vector<int> > inv;
vector< vector<int> > val;

void compute_val_inv(int idx)
{
	int p = factorization[idx][0];
	int mod = factorization[idx][2];
	vector<int> cur_val(mod, 0);
	vector<int> cur_inv(mod, 0);
	cur_val[0]=1; 
	for(int i=1 ; i<=mod-1 ; i++)
	{
		if(i%p==0) cur_val[i]=cur_val[i-1];
		else cur_val[i]=(1LL*cur_val[i-1]*i)%mod;
	}
	cur_inv[1]=1;
	for(int i=2 ; i<=mod-1 ; i++)
	{
		if(i%p==0) continue;
		cur_inv[i]=minv(i, mod);
	}
	val.push_back(cur_val); 
	inv.push_back(cur_inv);
}

void precompute_everything(int mod)
{
	for(int i=2 ; i*i<=mod ; i++)
	{
		if(mod%i==0)
		{
			int cnt=0, v=1;
			while(mod%i==0) { mod=mod/i; v=v*i; cnt++; }
			vector<int> prime_power{i, cnt, v};
			factorization.push_back(prime_power);
		}
	}
	if(mod!=1)
	{
		vector<int> prime_power{mod, 1, mod};
		factorization.push_back(prime_power);
	}
	for(int idx=0 ; idx<factorization.size() ; idx++) compute_val_inv(idx);
}

pair<int, int> factorial_p(int n, int idx)
{
	int p = factorization[idx][0];
	int mod = factorization[idx][2];
	if(n<p) return make_pair(0, val[idx][n]);  
	int k = n/p; 
	pair<int, int> V = factorial_p(k, idx);
	int e = V.first + k;
	int kp = n/mod; int rp = n%mod;
	int m = V.second;
	m = (1LL * m * exp(val[idx][mod-1], kp % 2, mod)) % mod;
	m = (1LL * m * val[idx][rp]) % mod;
	return make_pair(e, m);
}

int ncr_case_3_method_2(int n, int k, int idx)
{
	int p = factorization[idx][0];
	int ex = factorization[idx][1];
	int mod = factorization[idx][2];
	if(n<0 || k<0 || n<k) return 0;
	pair<int, int> V1 = factorial_p(n, idx);
	pair<int, int> V2 = factorial_p(k, idx);
	pair<int, int> V3 = factorial_p(n-k, idx);
	int e = V1.first - V2.first - V3.first;
	int m = V1.second;
	m = (1LL * m * inv[idx][V2.second]) % mod;
	m = (1LL * m * inv[idx][V3.second]) % mod;
	if(e >= ex) return 0;
	for(int i=1 ; i<=e ; i++) m = (1LL * m * p) % mod;
	return m;
}

void solve_tc(void)
{
	int n, k; cin >> n >> k;
	pair<int, int> cur = make_pair(0, 1);
	for(int idx=0 ; idx<factorization.size() ; idx++)
	{
		int mod_prime_power = ncr_case_3_method_2(n, k, idx);
		cur = solve(cur, make_pair(mod_prime_power, factorization[idx][2]));
	}
	cout << cur.first << "\n";
}

int main(void)
{
	fio; int tc; cin >> tc;
	int mod = 142857;
	precompute_everything(mod);
	while(tc--) solve_tc();
	return 0;
}