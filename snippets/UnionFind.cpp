/*
Weighted Union-find disjoint sets data structure, supporting path compression.
*/

#include <vector>
#include <iostream>
using namespace std;

typedef vector<int> vi;

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

int main() {
	UnionFind ufds = UnionFind(5);
	ufds.unionSet(0, 0);
	ufds.print();

	ufds.unionSet(0,1);
	ufds.unionSet(0,2);
	ufds.unionSet(3,4);
	ufds.print();

	return 0;
}
