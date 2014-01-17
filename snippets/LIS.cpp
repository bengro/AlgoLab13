#include <iostream>
#include <vector>
using namespace std;

void testcase() {
    int N; cin >> N;
    
    vector<int> S(N);
    vector<int> L(N, 1);
    L[0] = 0;

    for(int i = 0; i < N; ++i) {
        int i; 
        cin >> i;
        S[n] = i;
        
        for(int j = i-1; j > 0; --j) {
            if(S[i] > S[j] && L[j]+1 > L[i]) {
                L[i] = L[j] + 1;
            }
        }
    }
    
    cout << L[N-1] << "\n";
}

int main() {
    int TC; cin >> TC;
    while (TC--) testcase();
    return 0;
}
