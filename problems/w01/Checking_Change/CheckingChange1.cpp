#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void testcase() {
    int C, M; 
    cin >> C >> M;
    vector<int> change(10000, INT_MAX);
    for(int c = 0; c < C; ++c) {
        int coin; cin >> coin;
        change[coin] = 1;
    }
    
    int rightmost = 1;
    for(int m = 0; m < M; ++m) {
        int input; 
        cin >> input;

        if(rightmost < input) { 
            for(int i = rightmost+1; i <= input; ++i) {
                if(change[i] == 1) continue;
                int global_min = INT_MAX;
                for(int j = i-1; j > 0; --j) {
                    if(change[j] != INT_MAX && change[i-j] != INT_MAX)
                        global_min = min(global_min, change[j] + change[i-j]);
                }
                change[i] = global_min;
            }
            rightmost = input;
        }

        (change[input] == INT_MAX) ? cout << "not possible\n" : cout << change[input] << "\n";
    }
}

int main() {
    int TC; cin >> TC;
    while (TC--) testcase();
    return 0;
}
