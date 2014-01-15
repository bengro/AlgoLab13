#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vii;

void testcase() {
    int N; cin >> N;
    vi count;
    for(int n = 0; n < N; ++n) {
        int m; cin >> m;
        count.push_back(m);
    }
    
    vii lists(N);
    for(int n = 0; n < N; ++n) {
        for(int m = 0; m < count[n]; ++m) {
            int p; cin >> p;
            lists[n].push_back(p);
        }
    }

    priority_queue<pair<int, pair<int, int> > > max_heap;
    priority_queue<pair<int, pair<int, int> >, vector<pair<int, pair<int, int> > >, greater<pair<int, pair<int, int> > > > min_heap;
    for(int n = 0; n < N; ++n) {
        max_heap.push(make_pair(lists[n][0], make_pair(n, 0)));
        min_heap.push(make_pair(lists[n][0], make_pair(n, 0)));
    }
    
    int min_interval = INT_MAX;
    while(true) {
        pair<int, pair<int, int> > a = min_heap.top();
        pair<int, pair<int, int> > b = max_heap.top();
        int interval = b.first - a.first + 1;

        min_interval = min(interval, min_interval);
        int min_list = a.second.first;
        int element = a.second.second;
        
        if(element+1 < lists[min_list].size()) {
            max_heap.push(make_pair(lists[min_list][element+1], make_pair(min_list, element+1)));
            min_heap.pop();
            min_heap.push(make_pair(lists[min_list][element+1], make_pair(min_list, element+1)));
        } else {
            break;
        }
    }

    cout << min_interval << "\n";
}

int main() {
    int TC; cin >> TC;
    while (TC--) testcase();
    return 0;
}
