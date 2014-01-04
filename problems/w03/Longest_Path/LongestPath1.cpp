#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> AdjacencyList;

void drill(int target, int comingFrom, AdjacencyList& adj, vi& max, vector<priority_queue<int> >& incomingPaths, vi& longest, bool start) {
	if(adj[target].size() == 1 && !start) {
		max[target] = 0;
		incomingPaths[comingFrom].push(1);
		return;
	}

	for(unsigned int outgoing = 0; outgoing < adj[target].size(); ++outgoing) {
		if(adj[target][outgoing] != comingFrom)
			drill(adj[target][outgoing], target, adj, max, incomingPaths, longest, false);
	}

	int first = incomingPaths[target].top(); incomingPaths[target].pop();
	int second = 0;
	if(!incomingPaths[target].empty()) {
		second = incomingPaths[target].top(); incomingPaths[target].pop();
	}

	max[target] = first;
	longest[target] = first + second;
	incomingPaths[comingFrom].push(first+1);
}

void testcase() {
	int vertices; cin >> vertices;

	if(vertices == 1) { int v1, v2; cin >> v1 >> v2; cerr << 1 << "\n"; return;	}

	AdjacencyList adj(vertices);
	vi max(vertices, 0); 
	vi longest(vertices, 0);
	vector<priority_queue<int> > incomingPaths(vertices);

	for(int input = 0; input < vertices-1; ++input) {
		int v1, v2; cin >> v1 >> v2;
		adj[v1].push_back(v2);
		adj[v2].push_back(v1);
	}

	drill(0, 0, adj, max, incomingPaths, longest, true);
	cout << *max_element(longest.begin(), longest.end())+1 << "\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	int TC; cin >> TC;
	while(TC--) testcase();
	return 0;
}