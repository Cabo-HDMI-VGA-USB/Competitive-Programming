// TITLE: HLD 
// COMPLEXITY:
// DESCRIPTION: 

#include <bits/stdc++.h>
 
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define endl '\n'
#define rep(i, a, b) for(int i=(int)(a);i < (int)(b);i++)
#define debug(var) cout << #var << ": " << var << endl
#define pii pair<int, int>
#define vi vector<int>
 
int MAX = 2e5;
int MOD=1e9+7;
int oo=2e9;
int segsize;
 
using namespace std;
 
vector<vector<int>> g;
vi pai, depth, heavy, sz, head, pos, weight;
int dfstime=0;
 
struct ST{
    int n; vector<int> t;
 
	void setup(int n) {
		this->n = n;
		t.assign(2*n, 0);
	}
 
    int f(int a, int b) { return max(a, b); }
 
 
    int query(int l, int r) { // [l, r]
		r--;
        int resl = -oo, resr = -oo;
        for(l+=n, r+=n+1; l<r; l>>=1, r>>=1) {
            if(l&1) resl = f(resl, t[l++]);
            if(r&1) resr = f(t[--r], resr);
        }
        return f(resl, resr);
    }
 
    void update(int p, int value) {
        for(t[p+=n]=value; p >>= 1;)
            t[p] = f(t[p<<1], t[p<<1|1]);
    }
};
ST seg;
 
void dfs(int a, int p=0, int d=0) {
	depth[a] = d;
	pai[a]=p;
	sz[a] = 1;
	for(auto& b : g[a]) {
		if (b == p) continue;		
		dfs(b, a, d+1);
		if (heavy[a] == -1 or sz[b] > sz[heavy[a]]) heavy[a] = b;
		sz[a] += sz[b];
	}
}
 
void decompose(int a, int p=0, int h=0) {
	pos[a] = dfstime++;
	head[a] = h;
	if (heavy[a] != -1 ){
		decompose(heavy[a], a, h);
	}
 
	for(auto& b : g[a]) {
		if (b == p or heavy[a] == b) continue;
		decompose(b, a, b);
	}
}
 
int query(int a, int b) {
	int sum = -oo;
	for (; head[a] != head[b]; b=pai[head[b]]) {
		if (depth[head[a]] > depth[head[b]]) swap(a, b);
		
		int cursum = seg.query(pos[head[b]], pos[b]+1);
		sum = max(sum, cursum);
	}
	if (depth[a] > depth[b]) swap(a, b);
	return max(sum, seg.query(pos[a], pos[b]+1));
}
 
 
void solve()
{
	int n;cin>>n;
	int q;cin>>q;
	
	g.assign(n, vector<int>());
	pai.assign(n, 0);
	depth.assign(n, 0);
	heavy.assign(n, -1);
	sz.assign(n, -1);
	head.assign(n, 0);
	pos.assign(n, -1);
	weight.assign(n, 0);
	rep(i, 0, n) cin >> weight[i];
	rep(i, 0, n-1) {
		int a,b;cin>>a>>b;a--;b--;			
		g[a].pb(b);
		g[b].pb(a);
	}
 
	seg.setup(n);
	dfs(0);
	decompose(0);
	rep(i, 0, n) {
		seg.update(pos[i], weight[i]);
	}
	
	rep(i, 0, q) {
		int t;cin>>t;
		if (t == 2) {
			int a,b;cin>>a>>b;a--;b--;
			cout << query(a, b) << endl;
		} else {
			int i, w;cin>>i>>w;i--;
			seg.update(pos[i], w);
		}
	}
}
 
 
signed main()
{
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t=1;
	// cin>>t;
	while(t--) solve();
}
