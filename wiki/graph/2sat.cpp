// TITLE: 2SAT
// COMPLEXITY: O(n+m), n = number of variables, m = number of conjunctions (ands).
// DESCRIPTION: Finds an assignment that makes a certain boolean formula true, or determines that such an assignment does not exist.

struct twosat {
	vi vis, degin;
	stack<int> tout;
	vector<vi> g, gi, con, sccg;
	vi repr, conv;
	int gsize;
	void dfs1(int a) {
		if (vis[a]) return;
		vis[a]=true;
	 
		for(auto& b : g[a]) {
			dfs1(b);	
		}
	 
		tout.push(a);
	}
 
	void dfs2(int a, int orig) {
		if (vis[a]) return;
		vis[a]=true;
		
		repr[a]=orig;
		sccg[orig].pb(a);
		for(auto& b : gi[a]) {
			if (vis[b]) {
				if (repr[b] != orig) { 
					con[repr[b]].pb(orig);
					degin[orig]++;
				}
				continue;
			}
			dfs2(b, orig);
		}
	 
	}
	// if s1 = 1 and s2 = 1 this adds a \/ b to the graph
	void addedge(int a, int s1,
				 int b, int s2) {
		g[2*a+(!s1)].pb(2*b+s2);
		gi[2*b+s2].pb(2*a+(!s1));
		
		g[2*b+(!s2)].pb(2*a+s1);
		gi[2*a+s1].pb(2*b+(!s2));
	}

	
	twosat(int nvars) {
		gsize=2*nvars;
	    g.assign(gsize, vi());
	    gi.assign(gsize, vi());
	    con.assign(gsize, vi());
	    sccg.assign(gsize, vi());
		repr.assign(gsize, -1);
		vis.assign(gsize, 0);
		degin.assign(gsize, 0);
	}

	// returns empty vector if the formula is not satisfiable.
	vi run() {
		vi vals(gsize/2, -1);
		rep(i,0,gsize) dfs1(i);
		vis.assign(gsize,0);
		while(!tout.empty()) {
			int cur = tout.top();tout.pop();
			if (vis[cur]) continue;
			dfs2(cur,cur); 
			conv.pb(cur);
		}

		rep(i, 0, gsize/2) {
			if (repr[2*i] == repr[2*i+1]) {
				return {};
			}
		}
	 
		queue<int> q;
		for(auto& v : conv) {
			if (degin[v] == 0) q.push(v);
		}
			
		while(!q.empty()) {
			int cur=q.front(); q.pop();
			for(auto guy : sccg[cur]) {
				int	s = guy%2;
				int idx = guy/2;
				if (vals[idx] != -1) continue;
				if (s) {
					vals[idx] = false;
				} else {
					vals[idx]=true;
				}
			}
			for (auto& b : con[cur]) {
				if(--degin[b] == 0) q.push(b);
			}
		}

		return vals;
	}
}; 