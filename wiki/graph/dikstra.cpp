// TITLE: Dkistra
// COMPLEXITY: O(E + V.log(v))
// DESCRIPION: Finds to shortest path from start

int dist[mxN];
bool vis[mxN];
vector<pair<int, int>> g[mxN];

void dikstra(int start)
{
    fill(dist, dist + mxN, oo);
    fill(vis, vis + mxN, 0);
    priority_queue<pair<int, int>> q;
    dist[start] = 0;
    q.push({0, start});

    while(!q.empty()) {
        auto [d, a] = q.top();
        q.pop();
        if (vis[a]) continue;
        vis[a] = true;
        for (auto [b, w]: g[a]) {
            if (dist[a] + w < dist[b]) {
                dist[b] = dist[a] + w;
                q.push({-dist[b], b});
            }
        }
    }
}
