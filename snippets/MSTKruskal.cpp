#include <vector>
#include <iostream>
using namespace std;

typedef vector<int> vi;
typedef vector<pair<int, pair<int, int > > > EdgeList;

class UnionFind {
private: vi p, rank;
public:
	UnionFind(int N) {
		rank.assign(N, 0); 
		p.assign(N, 0);
		for(int i = 0; i < N; ++i) p[i] = i;
	}
	int findSet(int i) {
		return (p[i] == i) ? i : (p[i] = findSet(p[i]));
	}
	bool isSameSet(int i, int j) {
		return (findSet(i) == findSet(j));
	}
	void unionSet(int i, int j) {
		if(!isSameSet(i, j)) {
			int x = findSet(i); int y = findSet(j);		// path compression
			if(rank[x] < rank[y]) { p[i] = y; }			// weighted trees
			else {
				p[j] = x;
				if(rank[x] == rank[y]) rank[x]++;
			}
		}
	}
	void print() {
		for(int i = 0; i < p.size(); ++i) cout << i << " ";
		cout << "\n";
		for(int i = 0; i < p.size(); ++i) cout << p[i] << " ";
		cout << "\n";
		for(int i = 0; i < p.size(); ++i) cout << rank[i] << " ";
		cout << "\n";
	}
};

void kruskal_mst() {
	cout << "starting kruskal... \n";

	int n, m; cin >> n >> m;
	EdgeList edge_list;

	for(int edge = 0; edge < m; ++edge) {
		int v1, v2, w;
		cin >> v1 >> v2 >> w;
		edge_list.push_back(make_pair(w, make_pair(v1, v2)));
	}

	sort(edge_list.begin(), edge_list.end());
	
	UnionFind ufds(n);
	int mst_cost = 0;
	EdgeList graph;
	for(int e = 0; e < edge_list.size(); ++e) {
		pair<int, pair<int, int> > front = edge_list[e];
		if(!ufds.isSameSet(front.second.first, front.second.second)) {
			mst_cost += front.first;
			ufds.unionSet(front.second.first, front.second.second);
			graph.push_back(make_pair(front.first, make_pair(front.second.first, front.second.second)));
		}
	}
	cout << "MST weight: " << mst_cost << "\n";
	// graph contains a undirected MST.

}

int main() {
	int TC; cin >> TC;
	while(TC--) kruskal_mst();
	return 0;
}