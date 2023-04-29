// TITLE: DFS
// COMPLEXITY: O(N + M), N: Vertices, M: Arestas
// DESCRIPTION: Uma dfs simples

vector<int> adj[MAX];
void dfs(int a)
{
    if (visited[a]) return;
    visited[a] = true;

    for (auto b: adj[a]) {
        dfs(b);
    }
}

void solve(){
// Alguma coisa 
}
