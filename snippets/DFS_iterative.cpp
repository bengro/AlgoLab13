typedef vector<vi> AdjacencyList;
typedef vi State;

State states(5, UNVISITED);
AdjacencyList adj;
stack<int> lifo;

void dfs() {
	lifo.push(0);
	while(!lifo.empty()) {
		int vertex = lifo.top(); lifo.pop();
		states[vertex] = VISITED;
		cout << "Visiting " << vertex << "\n";

		for(int child = 0; child < adj[vertex].size(); ++child) {
			int child_vertex = adj[vertex][child];
			if(states[child_vertex] == UNVISITED) {
				lifo.push(child_vertex);
			}
		}
	}
}
