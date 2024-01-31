#include <bits/stdc++.h>

#define int long long
#define endl '\n'
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for(int i=(int)(a);i < (int)(b);i++)
#define pii pair<int, int>
#define vi vector<int>
#define vvi vector<vi>

#ifdef LOCAL
#define debug(var) cout << #var << ": " << var << endl
#else
#define debug(var)
#endif

using namespace std;

template<class T, class U> auto &operator>>(istream &is, pair<T, U> &p) { return is >> p.first >> p.second; }
template<class T, class U> auto &operator<<(ostream &os, pair<T, U> const& p) { return os << '{' << p.first << ' ' << p.second << '}'; }
const auto ES = "", SEP = " ";
template<class T> auto &operator>>(istream& is, vector<T> &c) { for (auto &x : c) is >> x; return is; }
template<class T> auto &operator<<(ostream& os, vector<T> const &c) { auto sep = ES; for (auto x : c) os << sep << x, sep = SEP; return os; }
template<class T> auto &operator<<(ostream& os, set<T> const &c) { auto sep = ES; for (auto x : c) os << sep << x, sep = SEP; return os; }
template<class T> auto &operator<<(ostream& os, multiset<T> const &c) { auto sep = ES; for (auto x : c) os << sep << x, sep = SEP; return os; }
template<class T> auto &operator<<(ostream& os, unordered_set<T> const &c) { auto sep = ES; for (auto x : c) os << sep << x, sep = SEP; return os; }
template<class T> auto &operator<<(ostream& os, deque<T> const &c) { auto sep = ES; for (auto x : c) os << sep << x, sep = SEP; return os; }
template<class K, class V> auto &operator<<(ostream& os, map<K,V> const &c) { auto sep = ES; for (auto x : c) os << sep << x, sep = SEP; return os; }
template<class K, class V> auto &operator<<(ostream& os, unordered_map<K,V> const &c) { auto sep = ES; for (auto x : c) os << sep << x, sep = SEP; return os; }

constexpr int MAX = 1e6+10;
constexpr int MOD=1e9+7;
constexpr int oo=0x3f3f3f3f3f3f3f3f;
vi fat,ifat;
int add(int x, int y) {
	return x+y >= MOD ? x+y-MOD : x+y;
}
int sub(int x, int y) {
	return x-y < 0 ? MOD+x-y : x-y;
}
int mul(int x, int y) {
	return (x*y) % MOD;
}

int fpow(int a,int b) {
	int x=1;
	while(b) {
		if (b&1) x = (a*x) % MOD;
		b/=2;
		a =(a*a)%MOD;
	}

	return x;
}
int inv(int a) {
	return fpow(a,MOD-2);
}

int choose(int n, int k) {
	if (k > n) return 0;
	return mul(fat[n], inv(mul(fat[n-k], fat[k])));
}

struct lagrange {
	vi ys;	
	int k;	
	lagrange(int k) : k(k) {}
	void addpoint(int y) {ys.pb(y);}
	int eval(int x) {
		int n=ys.size();
		vi pprod(n+1,1), sprod(n+1,1);
		
		rep(i,0,n) {
			pprod[i+1]=mul(pprod[i], sub(x, add(k, i)));
			sprod[n-i-1]=mul(sprod[n-i], sub(x, add(k,n-i-1)));
		}

		int ans=0;
		for (int i = 0; i < n; i++) {
			int num=mul(pprod[i], sprod[i+1]);
			int den=mul(ifat[i], ifat[n-i-1]);
			if ((n-i-1) % 2) den=sub(0,den);
			ans=add(ans,mul(mul(ys[i], num), den));
		}
		return ans;
	}

};

void solve()
{
	int n,k;cin>>n>>k;

	lagrange l(1);
	int sum=0;
	for(int i=1; i <= k+2; i++) {
		sum=add(sum, fpow(i, k));	
		l.addpoint(sum);
	}
	cout << l.eval(n) << endl;
}


signed main()
{
	#ifndef LOCAL
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	#endif

	fat.assign(MAX,1);
	ifat.assign(MAX,1);
	rep(i,1,MAX) fat[i] = mul(fat[i-1],i);
	ifat[MAX-1]=inv(fat[MAX-1]);
	for(int i=MAX-2; i >=0;i--) ifat[i] = mul(i+1,ifat[i+1]);

	int t=1;
	//cin>>t;
	while(t--) solve();
}
