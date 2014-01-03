#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>
#include <cmath>
using namespace std;

typedef vector<int> vi;

void testcase() {
	int n; cin >> n;
	vector<vi> posting_list(n);

	vi Npositions(n);
	for(int i = 0; i < n; ++i) { int m; cin >> m; Npositions[i] = m; }

	for(int word = 0; word < Npositions.size(); ++word) {
		for(int position = 0; position < Npositions[word]; ++position) {
			int input_position; cin >> input_position;
			posting_list[word].push_back(input_position);
		}
	}

	vi pointers(n, 0);
	priority_queue<int> max_heap;
	priority_queue<pair<int, int>, std::vector<pair<int, int> >, greater<pair<int, int> > > min_heap;

	for(int list = 0; list < n; ++list) {
		int value = posting_list[list][pointers[list]];
		max_heap.push(value); 
		min_heap.push(make_pair(value, list));
	}

	int min_interval = 1073741825;
	while(true) {
		pair<int, int> min_pair = min_heap.top(); min_heap.pop();
		int min_value = min_pair.first;
		int min_list = min_pair.second;
		
		int max_value = max_heap.top();
		int min_new = abs(max_value - min_value);
		min_interval = min(min_new, min_interval);
		
		if(pointers[min_list] == posting_list[min_list].size()-1) { break; }
		int jump = sqrt(posting_list[min_list].size());
		while((pointers[min_list]+jump < posting_list[min_list].size()-1) && 
			(posting_list[min_list][pointers[min_list]+jump] < min_heap.top().first)) {
			pointers[min_list] += jump;
		}
		pointers[min_list]++;

		int new_value = posting_list[min_list][pointers[min_list]];
		max_heap.push(new_value);
		min_heap.push(make_pair(new_value, min_list));
	}

	cout << min_interval+1 << "\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	int TC; cin >> TC;
	while(TC--) testcase();
	return 0;
}