// TITLE: Kosaraju
// COMPLEXITY: O(V+E)
// DESCRIPTION: Find the strongly connected components of a graph

struct Kosaraju {
	int N;
	vector<vector<int>> g, rg, cg;
	vector<bool> vis;
	vector<int> comp;
	stack<int> S;
	int CC = 0;

	Kosaraju(int n) {
		N = n;
		g.resize(N); rg.resize(N);
		vis.assign(N, 0); comp.assign(N, 0);
	}
	void add_edge(int a, int b) {
		g[a].pb(b);
		rg[b].pb(a);
	}
	void dfs(int a) {
		vis[a] = true;
		for (auto b: g[a]) if (!vis[b]) dfs(b);
		S.push(a);
	}
	void scc(int a, int c) {
		vis[a] = true;
		comp[a] = c;
		for (auto b: rg[a]) if (!vis[b]) scc(b, c);
	}
	void run() {
		vis.assign(N, 0);
		for (int i = 0; i < N; i++) if (!vis[i]) dfs(i);
		vis.assign(N, 0);
		while(!S.empty()) {
			auto a = S.top(); S.pop();
			if (!vis[a]) scc(a, CC++);
		}

		vis.assign(N, 0);
		vector<pair<int, int>> edges;

		for (int a = 0; a < N; a++) {
			// Add info to component here
			for (int b: g[a]) if (comp[a] != comp[b]) edges.eb(comp[a], comp[b]);
		}
		sort(all(edges));
		edges.erase(unique(all(edges)), edges.end());
		cg.resize(CC);
		for (const auto & [a, b]: edges) cg[a].pb(b);
	}
	void solve() {
	}
};

