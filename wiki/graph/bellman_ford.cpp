// TITLE: Bellman Ford
// COMPLEXITY: O(n * m) | n = |nodes|, m = |edges|
// DESCRIPTION: Finds shortest paths from a starting node to all nodes of the graph. Detects negative cycles, if they exist.

// a and b vertices, c cost
// [{a, b, c}, {a, b, c}]
vector<tuple<int, int, int>> edges;
int N;

void bellman_ford(int x){
	for (int i = 0; i < N; i++){
		dist[i] = oo;
	}
	dist[x] = 0;

	for (int i = 0; i < N - 1; i++){
		for (auto [a, b, c]: edges){
			if (dist[a] == oo) continue;
			dist[b]= min(dist[b], dist[a] + w);
		}
	}
}
// return true if has cycle
bool check_negative_cycle(int x){
	for (int i = 0; i < N; i++){
		dist[i] = oo;
	}
	dist[x] = 0;

	for (int i = 0; i < N - 1; i++){
		for (auto [a, b, c]: edges){
			if (dist[a] == oo) continue;
			dist[b]= min(dist[b], dist[a] + w);
		}
	}

	for (auto [a, b, c]: edges){
		if (dist[a] == oo) continue;
		if (dist[a] + w < dist[b]){
			return true;
		};
	}
	return false;
}
```
