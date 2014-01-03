#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

#define UNVISITED 0
#define VISITED 1
#define EXPLORED 2

typedef vector<int> vi;
typedef vector<vi> vii;
typedef pair<int, int> pi;

vi visited;
vi dfs_num;
vi dfs_low;

void dfs(int vertex, int parent, vii& adj, int counter) {
	for(signed int child = 0; child < adj[vertex].size(); ++child) {
		int child_vertex = adj[vertex][child];
		if(child_vertex != parent) {
			if(visited[child_vertex] == EXPLORED) {
				dfs_low[vertex] = min(dfs_num[child_vertex], dfs_low[vertex]);
			}

			if(visited[child_vertex] == UNVISITED) {
				visited[child_vertex] = EXPLORED;
				dfs_num[child_vertex] = ++counter;
				dfs_low[child_vertex] = dfs_num[child_vertex];
				dfs(child_vertex, vertex, adj, counter);
			}
		}
	}

	dfs_low[parent] = min(dfs_low[parent], dfs_low[vertex]);
	visited[vertex] = VISITED;
}

void testcase() {
	int N, M; cin >> N >> M; 
	visited.clear(); dfs_low.clear(); dfs_num.clear();
	vii adj(N); visited.assign(N, UNVISITED); dfs_num.assign(N, 0); dfs_low.assign(N, 0);

	if(N == 0 || N == 0) { cout << "0\n"; return; }

	for(int m = 0; m < M; ++m) {
		int v1, v2; cin >> v1 >> v2;
		adj[(v1-1)].push_back(v2-1);
		adj[(v2-1)].push_back(v1-1);
	}

	dfs_num[0] = 0; dfs_low[0] = 0; visited[0] = EXPLORED;
	dfs(0, 0, adj, 0);

	vector<pi> bridges;
	set<int> art_points;
	for(int u = 0; u < N; ++u) {
		for(int v = 0; v < adj[u].size(); ++v) {
			if(dfs_low[adj[u][v]] > dfs_num[u]) {
				bridges.push_back(make_pair(min(u, adj[u][v]), max(u, adj[u][v])));
			}
			if(dfs_low[adj[u][v]] >= dfs_num[u]) {
				// if it is not root, or it is root but has more than 1 child:
				art_points.insert(u);
			}
		}
	}
	sort(bridges.begin(), bridges.end());
	cout << bridges.size() << "\n";
	for(signed int b = 0; b < bridges.size(); ++b) {
		cout << bridges[b].first+1 << " " << bridges[b].second+1 << "\n";
	}
}

int main() {
	int TC; cin >> TC;
	while(TC--) testcase();
	return 0;
}