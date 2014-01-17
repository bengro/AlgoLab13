#include <iostream>
#include <vector>
using namespace std;

vector<int> S;
vector<int> L;

int f(int index) {
    if(L[index] != -1) return L[index];
    
    L[index] = 1;
    for(int j = index - 1; j >= 0; --j) {
        if(S[index] > S[j])
            L[i] = max(L[i], f(j) + 1);
    }
    return L[index];
}

void testcase() {
    int N; cin >> N;
    
    vector<int> S(N);
    vector<int> L(N, -1);
    for(int n = 0; n < N; ++n) {
        int input; cin >> input;
        S[n] = input;
    }
    
    cout << f(N-1) << "\n";
}

int main() {
    int TC; cin >> TC;
    while (TC--) testcase();
    return 0;
}
