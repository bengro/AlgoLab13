#include <iostream>
#include <vector>
#include <map>
#include <cmath>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vii;
typedef map<vector<int>, int> vector_int;

vi M;
int N;
vector_int dp_table;
vii chips;

int find_max(vi& state) {
    if(dp_table.count(state) == 1)
        return dp_table[state];

    for(int n = 1; n < pow(2.0, N); ++n) {
        vi new_state = state;
        int T = 0;
        int prev = -1;

        for(int k = 0; k < N; ++k) {
            if((n & (1 << k)) && (state[k] != 0)) {
                int color = chips[k][state[k]-1];
                if(prev == color || prev == -1) {
                    --new_state[k];
                    prev = color;
                    ++T;
                } else {
                    T = 0;  // !important to avoids wasted loops and computing invalid states.
                    break;
                }
            }
        }
        
        if(T != 0) { // if T=0, then invalid subset.
            int K = (T <= 1) ? 0 : pow(2.0, T-2);
            dp_table[state] = max(find_max(new_state) + K, dp_table[state]);
        } 
    }
    
    return dp_table[state];
}

void testcase() {
    cin >> N;
    M = vi(N);
    for(int n = 0; n < N; ++n)
        cin >> M[n];

    chips = vii(N);
    for(int n = 0; n < N; ++n) {
        for(int m = 0; m < M[n]; ++m) {
            int col; cin >> col;
            chips[n].push_back(col); 
        }
    }
    
    dp_table = vector_int();
    cout << find_max(M) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    int TC; cin >> TC;
    while(TC--) testcase();
    return 0;
}
