// TITLE: Kosaraju
// COMPLEXITY: O(V+E)
// DESCRIPTION: Find the strongly connected components of a graph

int n,m;
vector<vi> g, gi, scc;
vi vis, order, p;
 
void dfs1(int a) {
	if(vis[a]) return;
	vis[a]=true;
	for(auto& b:g[a]) {
		dfs1(b);
	}
	order.pb(a);
}
 
void dfs2(int a, int orig) {
	if (vis[a]) return;
	vis[a]=true;
	p[a]=orig;
 
	for(auto& b:gi[a]) {
		if (vis[b] && p[b] != orig)
			scc[p[b]].pb(orig);
		dfs2(b,orig);
	}
}

void solve() {
	cin>>n>>m;
 
	g.assign(n, vi());
	gi.assign(n, vi());
	scc.assign(n, vi());
	vis.assign(n, 0);
	p.assign(n, 0);
	rep(i, 0, m) {
		int a,b;cin>>a>>b;a--;b--;
		g[a].pb(b);
		gi[b].pb(a);
	}
 
	rep(i,0,n)dfs1(i);
	vis.assign(n,0);
	for(int i=n-1; i>=0;i--) dfs2(order[i],order[i]);
 
	vis.assign(n,0);
} 
