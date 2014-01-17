#include <iostream>
#include <vector>
#include <stack>
using namespace std;

#define VISITED 1
#define UNVISITED -1

typedef pair<int, int> p;
typedef vector<p> vp;
typedef vector<int> vi;

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

	dfs();

	return 0;
}
