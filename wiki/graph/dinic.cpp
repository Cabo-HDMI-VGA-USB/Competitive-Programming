struct Dinic {
  struct Edge {
    int a, b, cap, flow=0;
    Edge (int a, int b, int cap) : a(a), b(b), cap(cap) {}
  };

  vector<Edge> edges;
  vector<vector<int>> adj;
  vector<int> level, nxt;

  int n, s, t;
  Dinic(int n, int s, int t) : n(n), s(s), t(t) {
    adj.resize(n);
  }

  void add_edge(int a, int b, int cap) {
    edges.eb(a, b, cap);
    adj[a].pb(edges.size()-1);
    edges.eb(b, a, 0);
    adj[b].pb(edges.size()-1);
  }

  bool bfs() {
    queue<int> q;
    level.assign(n, -1);
    level[s] = 0;
    q.push(s);
    while (!q.empty()) {
      int a = q.front(); q.pop();
      for (auto eid : adj[a]) {
        auto e = edges[eid];
        if (e.cap - e.flow <= 0) continue;
        if (level[e.b] != -1) continue;
        level[e.b] = level[a] + 1;
        q.push(e.b);
      }
    }
    return level[t] != -1;
  }

  int dfs(int a, int f) {
    if (f == 0 || a == t) return f;
    for (int &cid = nxt[a]; cid < adj[a].size(); cid++) {
      int eid = adj[a][cid];
      auto &e = edges[eid];
      if (e.cap - e.flow <= 0) continue;
      if (level[e.b] != level[e.a] + 1) continue;
      int newf = dfs(e.b, min(f, e.cap-e.flow));
      if (newf == 0) continue;
      e.flow += newf;
      edges[eid^1].flow -= newf;
      return newf;
    }
    return 0;
  }

  int flow() {
    int f = 0;
    while (bfs()) {
      nxt.assign(n, 0);
      while (int newf = dfs(s, oo))
        f += newf;
    }
    return f;
  }
};

