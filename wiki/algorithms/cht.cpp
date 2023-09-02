// TITLE: CHT
// COMPLEXITY:
// DESCRIPTION: 

#include<bits/stdc++.h>
 
#define int long long
#define ll long long
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define endl '\n'
#define pii pair<int, int>
#define rep(i,a,b) for(int i = (int)(a); i < (int)(b); i++)
#define debug(var) cout << #var << ": " << var << endl
#define vi vector<int>
 
constexpr int oo = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 1e9+7;
constexpr int MAX = (int)2e5;
//g++ m.cpp -std=c++17 -ggdb -fsanitize=address -Wall -o m && ./m
 
using namespace std;
 
struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};
 
struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		k=-k;
		m=-m;
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return -(l.k * x + l.m);
	}
};
 
void solve()
{
	int n,x;cin>>n>>x;
 
	vi f(n+1), s(n+1), dp(n+1);
	
	f[0]=x;
	rep(i, 1, n+1) {
		cin>>s[i];
	}
	rep(i, 1, n+1) {
		cin>>f[i];
	}
 
	dp[n] = 0;
	LineContainer cvt;
	cvt.add(s[n], 0);
	for(int i = n-1; i >= 0; i--) {
		dp[i]=cvt.query(f[i]);	
		if (i > 0)
			cvt.add(s[i], dp[i]);
	}
 
	cout << dp[0];
 
}
 
signed main()
{
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t=1;
	//cin>>t;
	while(t--)solve();
}
