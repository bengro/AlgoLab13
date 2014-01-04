#include <vector>
#include <iostream>
using namespace std;

#define UNDEFINED -1
typedef vector<int> vi;
typedef vector<vi> vii;

int subsequence(int left, int right, vi& coins, vii& dp_table) {
	if(dp_table[left][right] != UNDEFINED) return dp_table[left][right];
	
	if(left > right) left = right;
	if(left == right) return dp_table[left][right] = coins[left]; 
	if(right - left == 1) return dp_table[left][right] = max(coins[left], coins[right]); 

	int min_left = min(subsequence(left+2, right, coins, dp_table), subsequence(left+1, right-1, coins, dp_table));
	int min_right = min(subsequence(left, right-2, coins, dp_table), subsequence(left+1, right-1, coins, dp_table));
	return dp_table[left][right] = max(coins[left]+min_left, coins[right]+min_right);
}

void testcase() {
	int n; cin >> n;
	vi coins(n);
	for(int i = 0; i < n; ++i) {
		int input; cin >> input;
		coins[i] = input;
	}

	vii dp_table(n, vi(n, UNDEFINED));
	subsequence(0, n-1, coins, dp_table);
	cout << dp_table[0][n-1] << "\n";
}

int main() {
	int TC; cin >> TC;
	while(TC--) testcase();
	return 0;
}