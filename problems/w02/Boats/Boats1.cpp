#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

void testcase() {
    int N; cin >> N;
    vector<pair<int, int> > boats;  // sorted by ring position.
    for(int n = 0; n < N; ++n) {
        int l, p; cin >> l >> p;
        boats.push_back(make_pair(p, l));
    }
    sort(boats.begin(), boats.end());
    
    int counter = 1;
    int best_boat;
    int best_right = INT_MAX;
    int right = boats[0].first;
    int b = 1;
    while(b < N) {
        if(boats[b].first < right) { ++b; continue; }
        int temp = max(boats[b].first, boats[b].first + boats[b].second - (boats[b].first - right));

        if(temp < best_right) {
            best_boat = b; 
            best_right = temp;
        }
        
        if((boats[b].first >= best_right) || (b + 1 == N && boats[b].first >= right)) {
            b = best_boat;
            right = best_right;
            best_right = INT_MAX;
            ++counter;
        }
        ++b;
    }
    cout << counter << "\n";
}

int main() {
    int TC; cin >> TC;
    while (TC--) testcase();
    return 0;
}
