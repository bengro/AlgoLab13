/*
Prims approach for the minimum spanning tree is based on a ordering of edge weights by a priority_queue.
We start at a arbitrary vertex (which will be part of the MST) and we explore all children. 
We put all the children weights in the priority queue (min heap). We then pop the front and add it to visited. 
We explore all the children of the front element and put them in the min heap. We process all edges in the min-heap.
*/

#include <vector>
#include <queue>
#include <iostream>
#include <functional>
using namespace std;

#define FREE 1
#define TAKEN 2

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<vector<ii> > AdjList;

void process(int vertex, AdjList& adj, vi& taken, priority_queue<ii, vector<ii>, greater<ii> >& min_heap) {
	taken[vertex] = TAKEN;
	for(int child = 0; child < adj[vertex].size(); ++child) {
		if(taken[adj[vertex][child].second] == FREE) {
			min_heap.push(make_pair(adj[vertex][child].first, adj[vertex][child].second));
		}
	}
}

void prim_mst() {
	int n, m; cin >> n >> m;
	AdjList adj(n);
	vi taken(n, FREE);

	// O(E)
	for(int e = 0; e < m; ++e) {
		int v1, v2, w; cin >> v1 >> v2 >> w;
		adj[v1].push_back(make_pair(w, v2));
		adj[v2].push_back(make_pair(w, v1));
	}

	priority_queue<ii, vector<ii>, greater<ii> > min_heap;
	process(0, adj, taken, min_heap);

	// O(E * log E)
	int mst_cost = 0;
	while(!min_heap.empty()) {
		ii front = min_heap.top(); min_heap.pop();
		if(taken[front.second] == FREE) { 
			mst_cost += front.first;
			process(front.second, adj, taken, min_heap);
		}
	}

	cout << "mst_cost: " << mst_cost << "\n";
}

int main() {
	int TC; cin >> TC;
	while(TC--) prim_mst();
	return 0;
}