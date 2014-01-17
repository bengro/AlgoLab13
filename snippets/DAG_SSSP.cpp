#include <iostream>
#include <vector>
#include <utility>
#include <queue>
using namespace std;

typedef vector<vector<pair<int, int> > > AdjacencyList;
typedef vector<int> vi;

void testcase() {
	int n, m; cin >> n >> m;

	AdjacencyList adj(n);
	vi incoming(n, 0);
	vi sssp(n, 0);

	for(int e = 0; e < m; ++e) {
		int v1, v2, w;
		cin >> v1 >> v2 >> w;
		adj[v1].push_back(make_pair(v2, w));
		incoming[v2] += 1;
	}

	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > topo_order;
	for(int i = 0; i < n; ++i) {
		topo_order.push(make_pair(incoming[i], i));
	}

	// gives me a topological order
	while(!topo_order.empty()) {
		pair<int, int> vertex = topo_order.top(); topo_order.pop();
		if(vertex.first == 0) sssp[vertex.second] = 0;
		for(int i = 0; i < adj[vertex.second].size(); ++i) {
			pair<int, int> neighbour = adj[vertex.second][i];
			sssp[neighbour.first] = max(sssp[vertex.second] + neighbour.second, sssp[neighbour.first]);
			cout << vertex.second << " -> " << neighbour.first << " " << sssp[neighbour.first] << "\n";
		}
	}

	for(int s = 0; s < n; ++s) {
		cout << "s: " << s << " " << sssp[s] << "\n";
	}
}

int main() {
	int TC; cin >> TC;
	while(TC--) testcase();
	return 0;
}