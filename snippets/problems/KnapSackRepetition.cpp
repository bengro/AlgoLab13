/*
 Knapsack with repetition. We divide the problem of finding the minimum for a given W, into decreasing problems 0-W.
 For each w, we compute the maximal value. We add the maximums of the subproblems, to solve bigger and bigger problems.
 If we draw the DAG for this problem, we get a directed graph with W+1 vertices. The values correspond to the maximal value.  
 Essentially, we are finding the longest (with respect to weights) in this DAG from child to root.

 By keeping track of the predecessor, we can track the exact weights which go in the knapsack. 
 We use the index range between the subsequent maximal choices to determine the weights.

*/

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef vector<int> vi;

int main() {

	int N; int W; cin >> N >> W;

	vi predecessors(W+1);
	vi values(N+1, 0);
	vi dp_table(W+1, 0);
	vector<vi> knapsack(W+1);

	int min_weight = INT_MAX;

	for(int n = 0; n < N; ++n) {
		int value, weight;
		cin >> value >> weight;
		values[n] = value;
		dp_table[weight] = value;
		min_weight = min(weight, min_weight);
	}

	for(int w = min_weight+1; w < W+1; ++w) {
		int max_value = 0;
		int predecessor = -1;
		for(int k = w-1; k >= (w/2); k--) { // nice optimization! The other half is only repeating. 
			int local_max = max(dp_table[k] + dp_table[w-k], max_value);
			if(local_max > max_value) {
				max_value = local_max;
				predecessor = k;	
			}
		}
		predecessors[w] = predecessor;
		dp_table[w] = max_value;
	}

	cout << "maximal value: " << dp_table[W] << "\n";
	int pred = predecessors[W];
	int prev = W;
	while(true) {
		int weight;
		if(prev == pred) {
			weight = prev;
			break;
		} else {
			weight = prev - pred;
		}
		cout << weight << " " ;
		prev = pred;
		pred = predecessors[pred];
	}
	cout << "\n";

	return 0;
}