// TITLE: Dinic Min cost
// COMPLEXITY: O(V*V*E), Bipartite is O(sqrt(V) E)
// DESCRIPTION: Gives you the max_flow with the min cost

// Edge structure
struct Edge
{
    int from, to;
    int flow, capacity;
    int cost;

    Edge(int from_, int to_, int flow_, int capacity_, int cost_)
        : from(from_), to(to_), flow(flow_), capacity(capacity_), cost(cost_)
    {}
};

struct Dinic
{
    vector<vector<int>> graph;
    vector<Edge> edges;
    vector<int> dist;
    vector<bool> inqueue;
    int size;
    int cost = 0;

    Dinic(int n)
    {
        graph.resize(n);
        dist.resize(n);
        inqueue.resize(n);
        size = n;
        edges.clear();
    }

    void add_edge(int from, int to, int capacity, int cost)
    {
        edges.emplace_back(from, to, 0, capacity, cost);
        graph[from].push_back(edges.size() - 1);

        edges.emplace_back(to, from, 0, 0, -cost);
        graph[to].push_back(edges.size() - 1);
    }

    int get_max_flow(int source, int sink)
    {
        int max_flow = 0;
        vector<int> next(size);
        while(spfa(source, sink)) {
            next.assign(size, 0);
            for (int f = dfs(source, sink, next, oo); f != 0; f = dfs(source, sink, next, oo)) {
                max_flow += f;
            }
        }
        return max_flow;
    }

    bool spfa(int source, int sink)
    {
        dist.assign(size, oo);
        inqueue.assign(size, false);
        queue<int> q;
        q.push(source);
        dist[source] = 0;
        inqueue[source] = true;

        while(!q.empty()) {
            int a = q.front();
            q.pop();
            inqueue[a] = false;

            for (int & b: graph[a]) {
                auto edge = edges[b];
                int cap = edge.capacity - edge.flow;
                if (cap > 0 && dist[edge.to] > dist[edge.from] + edge.cost) {
                    dist[edge.to] = dist[edge.from] + edge.cost;
                    if (not inqueue[edge.to]) {
                        q.push(edge.to);
                        inqueue[edge.to] = true;
                    }
                }
            }
        }
        return dist[sink] != oo;
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
            if (cap > 0 && (dist[edge.from] + edge.cost == dist[edge.to])) {
                int bottle_neck = dfs(edge.to, sink, next, min(flow, cap));
                if (bottle_neck > 0) {
                    edge.flow += bottle_neck;
                    rev_edge.flow -= bottle_neck;
                    cost += edge.cost * bottle_neck;
                    return bottle_neck;
                }
            }
        }
        return 0;
    }

    vector<pair<int, int>> mincut(int source, int sink)
    {
        vector<pair<int, int>> cut;
        spfa(source, sink);
        for (auto & e: edges) {
            if (e.flow == e.capacity && dist[e.from] != oo && level[e.to] == oo && e.capacity > 0) {
                cut.emplace_back(e.from, e.to);
            }
        }
        return cut;
    }
};

// Example on how to use
void solve()
{

    int N = 10;
    
    int source = 8;
    int sink = 9;

    Dinic flow(N);
    flow.add_edge(8, 0, 4, 0);
    flow.add_edge(8, 1, 3, 0);
    flow.add_edge(8, 2, 2, 0);
    flow.add_edge(8, 3, 1, 0);

    flow.add_edge(0, 6, oo, 3);
    flow.add_edge(0, 7, oo, 2);
    flow.add_edge(0, 5, oo, 0);
       
    flow.add_edge(1, 4, oo, 0);

    flow.add_edge(4, 9, oo, 0);
    flow.add_edge(5, 9, oo, 0);
    flow.add_edge(6, 9, oo, 0);
    flow.add_edge(7, 9, oo, 0);

    int ans = flow.get_max_flow(source, sink);
    debug(ans);
    debug(flow.cost);
}

int32_t main()
{
    solve();
}
