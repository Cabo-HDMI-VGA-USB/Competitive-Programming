// TITLE: Topological Sort
// COMPLEXITY: O(N + M), N: Vertices, M: Arestas
// DESCRIPTION: Retorna no do grapho em ordem topologica, se a quantidade de nos retornada nao for igual a quantidade de nos e impossivel

typedef vector<vector<int>> Adj_List;
typedef vector<int> Indegree_List; // How many nodes depend on him
typedef vector<int> Order_List;    // The order in which the nodes appears

Order_List kahn(Adj_List adj, Indegree_List indegree)
{
	queue<int> q;
	// priority_queue<int> q; // If you want in lexicografic order
	for (int i = 0; i < indegree.size(); i++) {
		if (indegree[i] == 0)
			q.push(i);
	}
	vector<int> order;

	while (not q.empty()) {
		auto a = q.front();
		q.pop();

		order.push_back(a);
		for (auto b: adj[a]) {
			indegree[b]--;
			if (indegree[b] == 0)
				q.push(b);
		}
	}
	return order;
}

int32_t main()
{

	Order_List = kahn(adj, indegree);
	if (Order_List.size() != N) {
		cout << "IMPOSSIBLE" << endl;
	}
	return 0;
}
