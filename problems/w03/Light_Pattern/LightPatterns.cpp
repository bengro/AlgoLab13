#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

#define SWAP 1
#define NO_SWAP 0
typedef vector<int> vi;
typedef vector<vi> vii;

void testcase() {
	int n, k, x; cin >> n >> k >> x;
	
	vi pattern;
	for(int i = k-1; i >= 0; i--) if(x - pow(2.0, i) >= 0) { x -= pow(2.0, i); pattern.push_back(1); } else { pattern.push_back(0); }

	vii changes(n/k, vi(2));
	for(int i = 0, p = 0, b = 0; i < n; ++i, ++p) {
		int input; cin >> input;
		(pattern[p] == input) ? changes[b][SWAP] += 1 : changes[b][NO_SWAP] += 1; 
		if(p == k-1) { p = -1; ++b; }
	}

	vii dp_table(n/k, vi(2));
	dp_table[0][SWAP] = changes[0][SWAP] + 1;
	dp_table[0][NO_SWAP] = changes[0][NO_SWAP];
	for(int b = 1; b < (n/k); ++b) {
		dp_table[b][SWAP] = min(dp_table[b-1][SWAP] + changes[b][SWAP], dp_table[b-1][NO_SWAP] + 2 + changes[b][SWAP]);
		dp_table[b][NO_SWAP] = min(dp_table[b-1][NO_SWAP] + changes[b][NO_SWAP], dp_table[b-1][SWAP] + changes[b][NO_SWAP]);
	}

	cout << min(dp_table[(n/k)-1][SWAP], dp_table[(n/k)-1][NO_SWAP]) << "\n";
}

int main() {
	int TC; cin >> TC;
	while(TC--) testcase();
	return 0;
}