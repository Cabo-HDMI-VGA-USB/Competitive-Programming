// TITLE: Dinic
// COMPLEXITY: O(V*V*E), Bipartite is O(sqrt(V) E)
// DESCRIPTION: Dinic is a strongly polynomial maximum flow algorithm, doesnt depend on capacity values good for matching

const int oo = 0x3f3f3f3f3f3f3f3f;
// Edge structure
struct Edge
{
    int from, to;
    int flow, capacity;

    Edge(int from_, int to_, int flow_, int capacity_)
        : from(from_), to(to_), flow(flow_), capacity(capacity_)
    {}
};

struct Dinic
{
    vector<vector<int>> graph;
    vector<Edge> edges;
    vector<int> level;
    int size;

    Dinic(int n)
    {
        graph.resize(n);
        level.resize(n);
        size = n;
        edges.clear();
    }

    void add_edge(int from, int to, int capacity)
    {
        edges.emplace_back(from, to, 0, capacity);
        graph[from].push_back(edges.size() - 1);

        edges.emplace_back(to, from, 0, 0);
        graph[to].push_back(edges.size() - 1);
    }

    int get_max_flow(int source, int sink)
    {
        int max_flow = 0;
        vector<int> next(size);
        while(bfs(source, sink)) {
            next.assign(size, 0);
            for (int f = dfs(source, sink, next, oo); f != 0; f = dfs(source, sink, next, oo)) {
                max_flow += f;
            }
        }
        return max_flow;
    }

    bool bfs(int source, int sink)
    {
        level.assign(size, -1);
        queue<int> q;
        q.push(source);
        level[source] = 0;

        while(!q.empty()) {
            int a = q.front();
            q.pop();

            for (int & b: graph[a]) {
                auto edge = edges[b];
                int cap = edge.capacity - edge.flow;
                if (cap > 0 && level[edge.to] == -1) {
                    level[edge.to] = level[a] + 1;
                    q.push(edge.to);
                }
            }
        }
        return level[sink] != -1;
    }

    int dfs(int curr, int sink, vector<int> & next, int flow)
    {
        if (curr == sink) return flow;
        int num_edges = graph[curr].size();

        for (; next[curr] < num_edges; next[curr]++) {
            int b = graph[curr][next[curr]];
            auto & edge = edges[b];
            auto & rev_edge = edges[b^1];

            int cap = edge.capacity - edge.flow;
            if (cap > 0 && (level[curr] + 1 == level[edge.to])) {
                int bottle_neck = dfs(edge.to, sink, next, min(flow, cap));
                if (bottle_neck > 0) {
                    edge.flow += bottle_neck;
                    rev_edge.flow -= bottle_neck;
                    return bottle_neck;
                }
            }
        }
        return 0;
    }
};

// Example on how to use
void solve()
{
    int n, m;
    cin >> n >> m;
    int N = n + m + 2;

    int source = N - 2;
    int sink = N - 1;

    Dinic flow(N);

    for (int i = 0; i < n; i++) {
        int q; cin >> q;
        while(q--) {
            int b; cin >> b;
            flow.add_edge(i, n + b - 1, 1);
        }
    }
    for (int i =0; i < n; i++) {
        flow.add_edge(source, i, 1);
    }
    for (int i =0; i < m; i++) {
        flow.add_edge(i + n, sink, 1);
    }
    
    cout << m - flow.get_max_flow(source, sink) << endl;

    // Getting participant edges
    for (auto & edge: flow.edges) {
        if (edge.capacity == 0) continue; // This means is a reverse edge
        if (edge.from == source || edge.to == source) continue;
        if (edge.from == sink   || edge.to == sink) continue;
        if (edge.flow == 0) continue; // Is not participant
        
        cout << edge.from + 1 << " " << edge.to -n + 1 << endl;
    }
}
