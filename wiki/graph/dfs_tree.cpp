// TITLE: Dfs tree
// COMPLEXITY: O(E + V)
// DESCRIPION: Create dfs tree from graph

int desce[mxN], sobe[mxN];
int backedges[mxN], vis[mxN];
int pai[mxN], h[mxN];

void dfs(int a, int p) {
    if(vis[a]) return;
    pai[a] = p;
    h[a] = h[p]+1;
    vis[a] = 1;

    for(auto b : g[a]) {
        if (p == b) continue;
        if (vis[b]) continue;
        dfs(b, a);
        backedges[a] += backedges[b];
    }
    for(auto b : g[a]) {
        if(h[b] > h[a]+1)
            desce[a]++;
        else if(h[b] < h[a]-1)
            sobe[a]++;
    }
    backedges[a] += sobe[a] - desce[a];
}
