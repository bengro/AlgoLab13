#include <vector>
#include <iostream>
#include <queue>
using namespace std;

typedef vector<unsigned long int> vi;

void testcase() {
	int n, k; cin >> n >> k;
	int input; cin >> input; // ignore first input.
	
	priority_queue<pair<long unsigned int, int>, vector<pair<long unsigned int, int> >, greater<pair<long unsigned int, int> > > min_heap;
	
	vi dp_table;
	dp_table.push_back(0);
	
	for(int i = 1; i < n; ++i) {
		while((!min_heap.empty()) && (min_heap.top().second < max(0, i - k))) min_heap.pop();
		min_heap.push(make_pair(dp_table[i-1], i-1));

		int input; cin >> input;
		long unsigned int new_min = input + min_heap.top().first;
		dp_table.push_back(new_min);	
	}
	cout << dp_table[n-1] << "\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	int TC; cin >> TC;
	while(TC--) testcase();
	return 0;
}