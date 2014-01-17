#include <vector>
#include <iostream>
#include <list>
using namespace std;

#define VISITED 0
#define EXPLORED 1
#define UNVISITED 2
typedef vector<int> vi;
typedef vector<vi> vii;

void dfs(int to, int from, vii& adj, vi& visited, list<int>& topo_order) {
	visited[to] = EXPLORED;
	topo_order.push_back(to);
	for(int child = 0; child < adj[to].size(); ++child) {
		int child_vertex = adj[to][child];
		if(child_vertex != from && visited[child_vertex] == UNVISITED) {
			dfs(child_vertex, to, adj, visited, topo_order);
		}
		if(visited[child_vertex] == EXPLORED) {
			cout << "cycle detected. \n";
		}
	}
	visited[to] = VISITED;
}

void testcase() {
	int n, m; cin >> n >> m;
	vii adj(n);
	vi visited(n, UNVISITED);
	list<int> topo_order;

	for(int e = 0; e < n; ++e) {
		int v1, v2; cin >> v1 >> v2;
		adj[v1].push_back(v2);
	}
	dfs(0, 0, adj, visited, topo_order);

	for(list<int>::iterator it = topo_order.begin(); it != topo_order.end(); ++it) {
		cout << *it << " ";
	}
	cout << "\n";
	for(list<int>::reverse_iterator it = topo_order.rbegin(); it != topo_order.rend(); ++it) {
		cout << *it << " ";
	}
	cout << "\n";
}

int main() {
	int TC; cin >> TC;
	while(TC--) testcase();
	return 0;
}
