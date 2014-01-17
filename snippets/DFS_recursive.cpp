#include <iostream>
#include <vector>
using namespace std;

#define VISITED 1
#define UNVISITED -1

typedef pair<int, int> p;
typedef vector<p> vp;
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

int main() {
	vi v0;
	v0.push_back(1);
	v0.push_back(4);
	adj.push_back(v0);

	vi v1;
	v1.push_back(0);
	v1.push_back(2);
	v1.push_back(3);
	adj.push_back(v1);
	
	vi v2;
	v2.push_back(1);
	adj.push_back(v2);

	vi v3;
	v3.push_back(1);
	adj.push_back(v3);

	vi v4;
	v4.push_back(0);
	adj.push_back(v4);

	dfs(0);

	return 0;
}
