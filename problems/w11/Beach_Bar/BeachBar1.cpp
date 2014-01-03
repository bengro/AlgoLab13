#include <vector>
#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;

typedef vector<int> vi;
const int normalize = 1000000;

void testcase() {
    int N; cin >> N;
    vi points;
    for(int n = 0; n < N; ++n) {
        int x; cin >> x;
        points.push_back(x + normalize);
    }
    sort(points.begin(), points.end());
    
    int g_counter = INT_MIN;
    int g_length = INT_MIN;
    vi solution;
    for(int n = 0; n < N; ++n) {
        int start_interval = points[n];
        int end_interval = start_interval + 200;
        int k = n;
        int counter = 0;
        while(points[k] <= end_interval && k < N) {
            ++counter;
            ++k;
        }
        int length = (points[k-1] - start_interval);
        
        if(counter > g_counter || (counter == g_counter && length < g_length)) {
            g_counter = counter;
            g_length = length;
            solution.clear();
        }
        
        if(g_counter == counter && g_length == length) {
            int output =  start_interval + length/2 - normalize;
            solution.push_back(output);
            if(length % 2 != 0) {
                solution.push_back(output+1);
            }
        }
    }
    
    g_length = (g_length % 2 == 0) ? g_length/2 : g_length/2+1;
    cout << g_counter << " " << g_length <<"\n";
    for(int s = 0; s < solution.size(); ++s) {
        cout << solution[s];
        if(s != solution.size() - 1) cout << " ";
    }
    cout << "\n";
}

int main() {
    int TC; cin >> TC;
    while(TC--) testcase();
    return 0;
}
