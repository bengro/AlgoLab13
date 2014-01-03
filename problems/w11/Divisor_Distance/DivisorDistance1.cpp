#include <iostream>
#include <cmath>
using namespace std;

int ancestor(int v) {
    for(int k = 2; k <= ceil(sqrt(v)); ++k) {
        if(v % k == 0) return (v/k); 
    }
    return 1;
}

void testcase() {
    int N, C; cin >> N >> C;
    for(int c = 0; c < C; ++c) {
        int v1, v2; cin >> v1 >> v2;
        int counter = 0;
        while(v1 != v2) {
            ++counter;
            if(v1 < v2) {
                v2 = ancestor(v2);
            } else {
                v1 = ancestor(v1);
            }
        }
        cout << counter << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
	int TC; cin >> TC;
	while(TC--) testcase();
	return 0;
}
