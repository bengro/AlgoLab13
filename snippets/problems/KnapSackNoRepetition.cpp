#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

typedef vector<int> vi;

int main() {

	// read how many items there are, and how big our knapsack is.
	int items, maximum; cin >> items >> maximum;

	// read input, store in two arrays
	vi weights(items+1);
	vi values(items+1);
	for(int j = 1; j <= items; ++j) {
		int weight, value; cin >> weight >> value;
		weights[j] = weight; values[j] = value;
	}

	// dp table with dimensions: items x maximum+1.
	vector<vector<int> > dp_table(items+1, vector<int>(maximum+1));
	vector<vector<int> > keep(items+1, vector<int>(maximum+1));

	// filling first row with 0's: no item == no value!
	for(int col = 0; col < maximum+1; ++col) dp_table[0][col] = 0;

	// DP: Bottom-up
	for(int item = 1; item <= items; ++item) {
		for(int w = 0; w <= maximum; ++w) {
			if(weights[item] < w) {
				dp_table[item][w] = max(dp_table[item-1][w], values[item]+dp_table[item-1][w - weights[item]]);
				keep[item][w] = 1;
			} else {
				dp_table[item][w] = dp_table[item-1][w];
				keep[item][w] = 0;
			}
		}
	}

	// print dp-table
	for(int rows = 0; rows < dp_table.size(); ++rows) {
		for(int cols = 0; cols < dp_table[rows].size(); ++cols) {
			cout << dp_table[rows][cols] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
	
	// print indicator matrix for backtracking
	for(int rows = 0; rows < dp_table.size(); ++rows) {
		for(int cols = 0; cols < dp_table[rows].size(); ++cols) {
			cout << keep[rows][cols] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
	
	// backtrack
	int K = maximum;
	for(int n = items; n > 0; n--) {
		if(keep[n][K] == 1) {
			cout << n << " ";
			K = K - weights[n];
		}
	}
	cout << "\n";
	cout << "\n";

	cout << "Maximum value: " << dp_table[items][maximum] << "\n";
	return 0;
}