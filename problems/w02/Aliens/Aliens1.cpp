#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

typedef vector<pair<int, int> > vii;      // sorted by left, right.
bool sortDescAsc(const pair<int, int>& lhs, const pair<int, int>& rhs) {
    if(lhs.first == rhs.first)
        return (lhs.second > rhs.second);
    else
        return lhs.first < rhs.first;
}

void testcase() { 
    int n, m; 
    cin >> n >> m;
    vii intervals;
    int superior = n;
    for(int i = 0; i < n; ++i) {
        int pi, qi;
        cin >> pi >> qi;
        if(pi == 0 && qi == 0) {
            --superior;
            continue;
        }
        pair<int, int> entry = make_pair(pi, qi);
        intervals.push_back(entry);
    }

    sort(intervals.begin(), intervals.end(), sortDescAsc);
    
    int left = 0;
    int right = 0;
    for(int i = 0; i < intervals.size(); ++i) {
        if(i+1 < intervals.size() && intervals[i+1].first == intervals[i].first && intervals[i+1].second == intervals[i].second) 
            --superior;
        else if(left == intervals[i].first && right == intervals[i].second) 
            --superior;
        else if(right >= intervals[i].second)
            --superior;
        
        if(right < intervals[i].second) {
            left = intervals[i].first;
            if(right != 0 && left-right > 1) {
                cout << "0\n";
                return;
            }
            right = intervals[i].second;
        }
   }
    
    cout << superior << "\n";
}

int main() {
    int TC;
    cin >> TC;
    while(TC--) testcase();
}

