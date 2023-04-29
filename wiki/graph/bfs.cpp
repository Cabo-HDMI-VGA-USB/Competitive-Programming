// TITLE: BFS
// COMPLEXITY: O(N + M), N: Vertices, M: Arestas
// DESCRIPTION: Uma bfs simples

vector<int> adj[MAX];
bool visited[MAX];

void bfs(int start)
{
    queue<int> q;
    q.push(start);

    while(not q.empty()){
        auto a = q.top();
        q.pop();
        if (visited[a]) continue;
        visited[a] = true;
        for (auto b: adj[a]){
            q.push(b);
        }
    }
}

void solve(){
// Alguma coisa 
}
