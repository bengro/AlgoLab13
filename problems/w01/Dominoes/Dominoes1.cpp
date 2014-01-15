#include <vector>
#include <iostream>
using namespace std;

void testcase() {
    int N; cin >> N;
    vector<int> tiles;
    for(int i = 0; i < N; ++i) {
        int h; cin >> h;
        tiles.push_back(h);
    }

    int rightmost = 0;
    int sum = N;
    for(int i = 0; i < N; ++i) {
        int j = tiles[i] + i - 1;
        rightmost = max(rightmost, j);
        if(rightmost >= N-1) break;
        if(i >= rightmost) {
            sum = rightmost+1;
            break;
        }
    }
    cout << sum << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int TC; cin >> TC;
    while(TC--) testcase();
}
