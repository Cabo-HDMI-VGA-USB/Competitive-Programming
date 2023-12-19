// TITLE: Bipartite Matching
// COMPLEXITY: E * sqrt(V)
// DESCRIPTION: Fast matching on bipartite graph

struct Bipartite {
    vector<int> nxt, match, dist;
    vector<bool> paired;
    vector<vector<int>> g;

    int n = 0, m = 0;

    Bipartite(int n_, int m_) {
        n = n_;
        m = m_;
        nxt.assign(n, 0);
        dist.assign(n, 0);
        paired.assign(n, 0);
        g.assign(n, vector<int>());
        
        match.assign(m, -1);
    }

    void add(int a, int b) {
        g[a].pb(b);
    }

    bool bfs() {
        fill(all(dist), n);
        queue<int> q;
        for (int a = 0; a < n; a++) {
            if (paired[a]) continue;
            dist[a] = 0;
            q.push(a);
        }
        bool found = false;
        while(!q.empty()) {
            int a = q.front(); q.pop();
            for (int b: g[a]) {
                int c = match[b];
                found |= c == -1;
                if (c == -1) continue;
                if (dist[a] + 1 < dist[c]) {
                    dist[c] = dist[a] + 1;
                    q.push(c);
                }
            }
        }
        return found;
    }

    bool kuhn(int a) {
        while(nxt[a] < (int)g[a].size()) {
            int b = g[a][nxt[a]++];
            int & c = match[b];
            if (c == -1 || (dist[a] + 1 == dist[c] && kuhn(c))) {
                c = a;
                paired[a] = true;
                return true;
            }
        }
        return false;
    }

    vector<pair<int, int>> get_match() {
        for (int a = 0; a < n; a++) shuffle(all(g[a]), rng);
        while(bfs()) {
            fill(all(nxt), 0);
            for (int a = 0; a < n; a++) {
                if (paired[a]) continue;
                kuhn(a);
            }
        }
        vector<pair<int, int>> ans;
        for (int b = 0; b < m; b++) {
            if (match[b] != -1) ans.eb(match[b], b);
        }
        return ans;
    }
};

