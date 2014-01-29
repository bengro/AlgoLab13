typedef vector<int> vi;
typedef vector<vi> AdjacencyList;
typedef vi State;

State states(6, UNVISITED);
AdjacencyList adj;

void dfs(int vertex) {
	cout << "visiting child: " << vertex << "\n";
	states[vertex] = VISITED;

	for(int neighbour = 0; neighbour <= adj[vertex].size(); ++neighbour) {
		int child = adj[vertex][neighbour];
		if(states[child] == UNVISITED) {
			dfs(child);
		}
	}
}