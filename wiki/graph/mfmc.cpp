struct Dinic {
  struct Edge {
r   int a, b, cap, flow=0, cost;
    Edge (int a, int b, int cap, int cost) 
	: a(a), b(b), cap(cap), cost(cost) {}
  };

  vector<Edge> edges;
  vector<vector<int>> adj;
  vector<int> nxt;
  vector<int> dist;
  int cost = 0;

  int n, s, t;
  Dinic(int n, int s, int t) : n(n), s(s), t(t) {
    adj.resize(n);
  }

  void add_edge(int a, int b, int cap, int cost) {
    edges.eb(a, b, cap, cost);
    adj[a].pb(edges.size()-1);
    edges.eb(b, a, 0, -cost);
    adj[b].pb(edges.size()-1);
  }

  bool spfa() {
    queue<int> q;
	vector<bool> inqueue(n);
    dist.assign(n, oo);
    dist[s] = 0;
	inqueue[s] = true;
    q.push(s);
    while (!q.empty()) {
      int a = q.front(); q.pop();
	  inqueue[a] = false;

      for (auto eid : adj[a]) {
        auto e = edges[eid];
        if (e.cap - e.flow <= 0) continue;
		if (dist[a] + e.cost < dist[b]) {
			dist[e.b] = dist[a] + e.cost;
			if (!inqueue[e.b]) {
				q.push(e.b);
				inqueue[e.b] = true;
			}
		}
      }
    }
    return dist[t] != oo;
  }

  int dfs(int a, int f) {
    if (f == 0 || a == t) return f;
    for (int &cid = nxt[a]; cid < adj[a].size(); cid++) {
      int eid = adj[a][cid];
      auto &e = edges[eid];
      if (e.cap - e.flow <= 0) continue;
      if (dist[e.b] != dist[a] + e.cost) continue;
      int newf = dfs(e.b, min(f, e.cap-e.flow));
      if (newf == 0) continue;
      e.flow += newf;
      edges[eid^1].flow -= newf;
	  cost += e.cost * newf;
      return newf;
    }
    return 0;
  }

  int flow() {
    int f = 0;
    while (spfa()) {
      nxt.assign(n, 0);
      while (int newf = dfs(s, oo))
        f += newf;
    }
    return f;
  }
};

