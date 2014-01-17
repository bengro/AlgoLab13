// Plain vanilla BFS on a unweighted graph.

#include <vector>
#include <iostream>
#include <queue>
using namespace std;

#define VISITED 1
#define UNVISITED 0

typedef vector<int> vi;
typedef vector<vi> AdjacencyList;

void bfs(AdjacencyList& adjacency) {
	vi status (adjacency.size(), UNVISITED);
	vi distance (adjacency.size(), 0);

	queue<int> lifo;

	lifo.push(0);
	status[0] = VISITED;

	while(!lifo.empty()) {
		int vertex = lifo.front(); lifo.pop();
		cout << "visiting " << vertex << "\n";

		for(int neighbour = 0; neighbour < adjacency[vertex].size(); neighbour++) {
			if(status[adjacency[vertex][neighbour]] == UNVISITED) {
				lifo.push(adjacency[vertex][neighbour]);
				status[adjacency[vertex][neighbour]] = VISITED; // important to avoid unnecessary repetition!!
				distance[adjacency[vertex][neighbour]] = distance[vertex] + 1;
			}
		}
	}
	cout << "Shortest path from 0 to " << adjacency.size()-1 << " : " << distance[adjacency.size()-1] << "\n";

	// component check
	for(int vertex = 0; vertex < adjacency.size(); ++vertex) {
		if(status[vertex] == UNVISITED) cout << "Isolated vertex found. \n";
	}

}

void testcase() {
	int n, m; cin >> n >> m;
	AdjacencyList adjacency (n);

	for(int edge = 0; edge < m; ++edge) {
		int v1, v2, w;
		cin >> v1 >> v2 >> w;
		adjacency[v1].push_back(v2);
		adjacency[v2].push_back(v1);
	}

	bfs(adjacency);
}

int main() {
	int TC; cin >> TC;
	while(TC--) testcase();
	return 0;
}