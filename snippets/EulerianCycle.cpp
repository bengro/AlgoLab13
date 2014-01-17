#include <list>
#include <vector>
#include <iostream>
using namespace std;

typedef pair<int, bool> ii;
typedef vector<ii> vii;
list<int> cycle;
vector<vii> adj;

void EulerianCycle(list<int>::iterator it, int u) {
	cycle.insert(it, u);
	cout << "u: " << u << "\n";
	for(int i = 0; i < adj[u].size(); ++i) {
		ii& v = adj[u][i];
		cout << "first: " << v.first << "\n";
		if(v.second) {
			v.second = false;
			for(int j = 0; j < adj[v.first].size(); ++j) {
				ii& uu = adj[v.first][j];
				if(uu.first == u && uu.second) {
					uu.second = false;
					break;
				}
			}
			EulerianCycle(cycle.end(), v.first);
		}
	}
}

void testcase() {
	cycle.clear();
	adj.clear();

	int n, m; cin >> n >> m;
	adj.resize(n); // how to in C++ 98?

	for(int e = 0; e < m; ++e) {
		int v1, v2; cin >> v1 >> v2;
		adj[v1].push_back(make_pair(v2, true));
		adj[v2].push_back(make_pair(v1, true));
	}

	EulerianCycle(cycle.begin(), 0);

	cout << "cycle/path of length " << cycle.size() << "\n";
	for(list<int>::iterator it = cycle.begin(); it != cycle.end(); ++it) {
		cout << *it << " ";
	}
	cout << "\n";

}

int main() {
	int TC; cin >> TC;
	while(TC--) testcase();
	return 0;
}